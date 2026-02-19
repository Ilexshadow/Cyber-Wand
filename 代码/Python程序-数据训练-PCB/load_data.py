import os
import numpy as np
import pandas as pd

def load_data(data_dir="calibrated_recordings"):
    X, y = [], []
    label_names = []
    for root, dirs, files in os.walk(data_dir):
        for file in files:
            if file.endswith('.csv'):
                label = os.path.basename(root)
                if label not in label_names:
                    label_names.append(label)
                label_idx = label_names.index(label)
                data = pd.read_csv(os.path.join(root, file), header=None).values
                if data.shape[1] < 3:
                    continue  # 跳过异常文件
                data = data[:, :3]  # 只取前三个指标
                if len(data) == 0:
                    continue  # 跳过空文件
                X.append(data)
                y.append(label_idx)
    label_names = sorted(label_names)
    return np.array(X).astype('float64'), np.array(y), label_names



'''
#打印数据基本信息

X, y, label_names = load_data(max_length=150)
print(f"数据形状: {X.shape} (样本数, 时间步长, 特征数)")
print(f"类别: {label_names}")
# 检查标签编码与label_names顺序
print("标签编码与类别名对应关系：")
for idx, name in enumerate(label_names):
    print(f"标签编号 {idx} -> 类别名 {name}") 



#可视化数据分布

import matplotlib.pyplot as plt
import numpy as np

# 1. 类别分布柱状图
plt.figure(figsize=(6, 4))
unique, counts = np.unique(y, return_counts=True)
plt.bar([label_names[i] for i in unique], counts)
plt.title("Type Distribution")
plt.xlabel("Type")
plt.ylabel("Count")
plt.show()

# 2. 计算每个类别每个通道的平均值，并画出每个类别全部通道的曲线
num_classes = len(label_names)
num_channels = X.shape[2]
fig, axes = plt.subplots(num_classes, 1, figsize=(12, 3*num_classes), sharex=True)
if num_classes == 1:
    axes = [axes]
for idx, label in enumerate(unique):
    class_samples = X[y == label]  # shape: (样本数, 时间步, 通道数)
    mean_curve = class_samples.mean(axis=0)  # shape: (时间步, 通道数)
    for ch in range(num_channels):
        axes[idx].plot(mean_curve[:, ch], label=f'Channel {ch+1}')
    axes[idx].set_title(f"Type:{label_names[label]} Mean Curve (All Channels)")
    axes[idx].set_ylabel("Sensor Value")
    axes[idx].legend()
    axes[-1].set_xlabel("Time Step")
plt.tight_layout()
plt.show()
'''
