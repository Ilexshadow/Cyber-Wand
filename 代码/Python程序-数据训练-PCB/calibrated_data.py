import os
import numpy as np

def low_pass_filter(input_data, alpha=0.3):
    """
    应用低通滤波
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


def process_data(calibration_rows=5,filter_alpha=0.3):
    # 定义根目录和输出目录
    root_dir = 'raw_recordings'
    output_dir = 'calibrated_recordings'

    # 定义各列的除数
    divisors = [1000, 1000, 2000, 1, 1, 1]  # 第1列÷1000，第2列÷1000，第3列÷2000，其他列÷1（保持不变）
    
    # 创建输出目录（如果不存在）
    os.makedirs(output_dir, exist_ok=True)

    # 获取所有子文件夹
    sub_folders = [f for f in os.listdir(root_dir) 
                  if os.path.isdir(os.path.join(root_dir, f))]
    
    # 处理每个子文件夹
    for folder in sub_folders:
        folder_path = os.path.join(root_dir, folder)
        output_folder_path = os.path.join(output_dir, folder)

        # 创建对应的输出子文件夹（如果不存在）
        os.makedirs(output_folder_path, exist_ok=True)

        # 获取所有数据文件
        data_files = [f for f in os.listdir(folder_path) 
                     if f.endswith('.csv')]  # 根据实际文件扩展名调整
        
        # 处理每个文件
        for file in data_files:
            file_path = os.path.join(folder_path, file)
            
            # 读取数据
            data = []
            with open(file_path, 'r') as f:
                for line in f:
                    line = line.strip()
                    if line:  # 跳过空行
                        # 解析每行的6个传感器数据，使用逗号分隔
                        row = list(map(float, line.split(',')))
                        if len(row) == 6:
                            data.append(row)
            
            if not data:
                print(f"Warning: No valid data found in {file_path}")
                continue
            
            # 转换为numpy数组便于处理
            data_array = np.array(data)
            
            # 应用低通滤波（与嵌入式代码保持一致）
            filtered_data = np.zeros_like(data_array)
            for col in range(6):  # 对所有6列数据进行滤波
                filtered_data[:, col] = low_pass_filter(data_array[:, col], filter_alpha)

            # 校准数据
            # 计算前calibration_rows行的平均值
            calibration_mean = np.mean(data_array[:calibration_rows], axis=0)
            
            # 所有行减去平均值
            calibrated_data = data_array - calibration_mean
            
            # 对各列进行除法处理
            for col_idx in range(6):
                calibrated_data[:, col_idx] = calibrated_data[:, col_idx] / divisors[col_idx]

            # 保存处理后的数据
            output_file = os.path.join(output_folder_path, f"calibrated_{file}")
            np.savetxt(output_file, calibrated_data, delimiter=',', fmt='%.6f')
            
            print(f"Processed: {file_path} -> {output_file}")

if __name__ == "__main__":
    # 可以调整前多少行用于校准，默认为5行
    process_data(calibration_rows=5, filter_alpha=0.3)