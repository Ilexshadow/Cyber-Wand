import serial
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import load_model #type:ignore
import time
import threading
from collections import deque

class SerialModelTester:
    def __init__(self, port='COM8', baudrate=115200, model_path='cyber_wand_model.h5'):
        # 初始化串口
        self.ser = serial.Serial(port, baudrate, timeout=1)
        self.running = False
        
        # 加载模型
        print("加载模型中...")
        self.model = load_model(model_path)
        print("模型加载完成")
        
        # 数据处理参数（与嵌入式代码保持一致）
        self.calibration_rows = 5
        self.filter_alpha = 0.3
        self.divisors = [1000, 1000, 2000, 1, 1, 1]
        
        # 数据缓冲区 - 保存原始数据
        self.raw_data_buffer = deque(maxlen=150)  # 稍微大一些，便于处理
        self.calibration_mean = None
        self.is_calibrated = False
        
        # 结果映射
        self.action_labels = {
            1: "1_Lumos",
            2: "2_Stupefy", 
            3: "3_Alohomora",
            4: "4_Oppugno",
            5: "5_Avada Kedavra",
            6: "6_Metelojinx Recanto",
            7: "7_Reparo",
            8: "8_Expelliarmus",
            9: "9_Expecto Patronum",
            0: "10_Incendio"
        }
    
    def low_pass_filter(self, input_data, alpha=0.3):
        """
        应用低通滤波（与process_data.py中的函数保持一致）
        input_data: 输入数据数组
        alpha: 滤波系数 (0-1)
        """
        filtered_data = np.zeros_like(input_data)
        for i in range(len(input_data)):
            if i == 0:
                filtered_data[i] = input_data[i]  # 第一个数据直接使用
            else:
                filtered_data[i] = alpha * input_data[i] + (1 - alpha) * filtered_data[i-1]
        return filtered_data

    def process_raw_data(self):
        """处理原始数据（与process_data.py中的处理逻辑保持一致）"""
        if len(self.raw_data_buffer) < self.calibration_rows:
            print(f"数据不足，需要至少 {self.calibration_rows} 行数据进行校准")
            return None
            
        # 转换为numpy数组
        data_array = np.array(list(self.raw_data_buffer))
        
        # 计算校准平均值（使用前calibration_rows行）
        calibration_mean = np.mean(data_array[:self.calibration_rows], axis=0)
        
        # 应用低通滤波
        filtered_data = np.zeros_like(data_array)
        for col in range(6):  # 对所有6列数据进行滤波
            filtered_data[:, col] = self.low_pass_filter(data_array[:, col], self.filter_alpha)

        # 所有行减去校准平均值
        calibrated_data = filtered_data - calibration_mean
        
        # 对各列进行除法处理
        for col_idx in range(6):
            calibrated_data[:, col_idx] = calibrated_data[:, col_idx] / self.divisors[col_idx]
            
        return calibrated_data

    def is_sensor_data(self, line):
        """检查是否是传感器数据行（包含6个用逗号分隔的数字）"""
        # 检查是否包含非数字字符（除了逗号和负号）
        if not all(c in '0123456789,-. ' for c in line):
            return False
        
        # 检查是否有6个数值
        parts = line.split(',')
        if len(parts) != 6:
            return False
        
        # 检查每个部分是否都是数字
        try:
            for part in parts:
                float(part.strip())
            return True
        except ValueError:
            return False

    def read_serial_data(self):
        """读取串口数据线程"""
        while self.running:
            try:
                if self.ser.in_waiting > 0:
                    line = self.ser.readline().decode('utf-8', errors='ignore').strip()
                    if line:
                        self.process_serial_line(line)
            except Exception as e:
                print(f"串口读取错误: {e}")
                time.sleep(0.1)
    
    def process_serial_line(self, line):
        """处理单行串口数据"""
        try:
            # 首先检查是否是控制信号
            clean_line = line.strip().lower()
            if clean_line == "start" or clean_line == "end":
                print(f"收到控制信号: {line}")
                if clean_line == "start":
                    # 开始新的数据采集
                    self.raw_data_buffer.clear()
                    self.calibration_mean = None
                    self.is_calibrated = False
                    print("开始数据采集...")
                elif clean_line == "end":
                    # 数据采集完成，进行预测
                    self.predict()
                return
            
            # 检查是否是传感器数据
            if not self.is_sensor_data(line):
                print(f"忽略非数据行: {line}")
                return
            
            # 解析传感器数据
            values = list(map(float, line.split(',')))
            if len(values) == 6:
                # 保存原始数据
                self.raw_data_buffer.append(values)
                
                # 实时显示（可选）
                if len(self.raw_data_buffer) % 10 == 0:
                    print(f"已采集 {len(self.raw_data_buffer)} 行原始数据")
                    
        except ValueError:
            print(f"数据解析错误: {line}")
        except Exception as e:
            print(f"处理错误: {e}")
    
    def predict(self):
        """使用模型进行预测"""
        if len(self.raw_data_buffer) < self.calibration_rows:
            print(f"数据不足，需要至少 {self.calibration_rows} 行数据进行校准")
            return
        
        print(f"开始处理 {len(self.raw_data_buffer)} 行数据进行预测...")
        
        # 处理原始数据
        processed_data = self.process_raw_data()
        if processed_data is None:
            print("数据处理失败")
            return
        
        # 转换为模型输入格式（只取前三列加速度数据）
        model_input = processed_data[:, :3]  # 只取AX, AY, AZ
        model_input = np.expand_dims(model_input, axis=0)  # 添加batch维度
        
        # 打印一些调试信息
        print(f"处理后的数据形状: {model_input.shape}")
        print(f"前几个数据点: {model_input[0, :5, :]}")
        
        # 进行预测
        try:
            predictions = self.model.predict(model_input, verbose=0)
            predicted_class = np.argmax(predictions[0])
            confidence = np.max(predictions[0])
            
            # 显示结果
            action_name = self.action_labels.get(predicted_class, "未知动作")
            print("=" * 50)
            print(f"预测结果: {action_name}")
            print(f"置信度: {confidence:.3f}")
            print("各类别概率:")
            for i, prob in enumerate(predictions[0]):
                label = self.action_labels.get(i, f"类别{i}")
                print(f"  {label}: {prob:.3f}")
            print("=" * 50)
            
        except Exception as e:
            print(f"预测错误: {e}")
    
    def start(self):
        """启动测试"""
        print("启动串口模型测试...")
        print("按下Ctrl+C停止")
        
        self.running = True
        # 启动串口读取线程
        self.serial_thread = threading.Thread(target=self.read_serial_data)
        self.serial_thread.daemon = True
        self.serial_thread.start()
        
        try:
            while self.running:
                time.sleep(0.1)
        except KeyboardInterrupt:
            self.stop()
    
    def stop(self):
        """停止测试"""
        self.running = False
        if hasattr(self, 'serial_thread') and self.serial_thread.is_alive():
            self.serial_thread.join(timeout=1)
        if hasattr(self, 'ser') and self.ser.is_open:
            self.ser.close()
        print("测试停止")

# 使用方法
if __name__ == "__main__":
    # 配置参数
    SERIAL_PORT = 'COM8'      # 根据您的串口修改（Windows: COM3, Linux: /dev/ttyUSB0）
    BAUD_RATE = 115200        # 与嵌入式代码保持一致
    MODEL_PATH = 'cyber_wand_model.h5'   # 您的模型文件路径
    
    # 创建测试器并启动
    tester = SerialModelTester(
        port=SERIAL_PORT,
        baudrate=BAUD_RATE,
        model_path=MODEL_PATH
    )
    
    tester.start()