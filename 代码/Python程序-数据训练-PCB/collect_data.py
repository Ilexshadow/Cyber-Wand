import serial
import time
from datetime import datetime
import os

# 配置参数
PORT = 'COM8'
BAUDRATE = 115200
DATA_DIR = "raw_recordings/10_Incendio"  # 存储所有录制数据的目录

# 1_Lumos，荧光闪烁，一上一下
# 2_Stupefy，昏昏倒地，左下锐角
# 3_Alohomora，阿拉霍洞开，phi
# 4_Oppugno，万箭齐发，下三角形
# 5_Avada Kedavra，阿瓦达索命，闪电
# 6_Metelojinx Recanto，消除气象咒，左牛角
# 7_Reparo，修复如初，顺时针圆
# 8_Expelliarmus，除你武器，右上直角
# 9_Expecto Patronum，呼神护卫，逆时针圆
# 10_Incendio，火焰熊熊，上三角形

# 创建存储目录
os.makedirs(DATA_DIR, exist_ok=True)

ser = serial.Serial(PORT, BAUDRATE, timeout=1)
ser.reset_input_buffer()
time.sleep(2)

is_recording = False
file_handle = None
sample_count = 0  # 样本计数器

print("等待按钮指令... (按下按钮开始/停止录制)")

def create_new_file():
    """创建带时间戳和序号的新文件"""
    global sample_count
    sample_count += 1
    timestamp = datetime.now().strftime('%Y%m%d_%H%M%S')
    filename = f"{DATA_DIR}/sample_{sample_count}_{timestamp}.csv"
    return open(filename, 'w'), filename

try:
    while True:
        if ser.in_waiting:
            line = ser.readline().decode('utf-8').strip()
            
            if line == "Start":
                if not is_recording:  # 避免重复开始
                    is_recording = True
                    file_handle, filename = create_new_file()
                    print(f"▶ 开始录制样本 #{sample_count} → {filename}")
                    
            elif line == "End":
                if is_recording:  # 避免重复停止
                    is_recording = False
                    file_handle.close()
                    print(f"■ 停止录制 | 已保存样本 #{sample_count}")
                    
            elif is_recording and file_handle:
                if line and not line.startswith(("START", "STOP")):
                    file_handle.write(line + '\n')
                    # 可选：实时显示数据点
                    print(f"{line}")

except KeyboardInterrupt:
    print("\n程序终止")
finally:
    if file_handle and not file_handle.closed:
        file_handle.close()
    ser.close()
    print(f"共录制 {sample_count} 个样本")