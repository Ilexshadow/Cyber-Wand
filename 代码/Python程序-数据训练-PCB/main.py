from tensorflow.keras.utils import to_categorical# type: ignore 

from load_data import load_data
from split_data import split_data
from build_model import build_model
from train_model import train_model
from nnom import *

def main():
    X,y, label_names = load_data()
    y = to_categorical(y, num_classes=10)

    X_train, X_test, y_train, y_test = split_data(X, y)
    model = build_model(input_shape=(100, 3), num_classes=len(label_names))
    history = train_model(model, X_train, y_train, X_test, y_test, epochs=200, batch_size=32)
    model.save('cyber_wand_model.h5')
    print("模型已保存为 'cyber_wand_model.h5'")
    
    # 生成NNOM模型
    generate_model(model, X_test, format='hwc', per_channel_quant=False, name="weights.h")

if __name__ == "__main__":
    main()
