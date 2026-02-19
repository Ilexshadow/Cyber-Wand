from tensorflow.keras import *# type: ignore
from tensorflow.keras.layers import *# type: ignore
from tensorflow.keras.activations import *# type: ignore

def build_model(input_shape, num_classes):
   inputs = layers.Input(shape=input_shape) # type: ignore

   x = layers.Conv1D(30, kernel_size=3, strides=3, padding='same')(inputs) # type: ignore
   x = layers.LeakyReLU()(x)# type: ignore
   x = layers.Conv1D(15, kernel_size=3, strides=3, padding='same')(x)# type: ignore
   x = layers.LeakyReLU()(x)# type: ignore
   
   x = layers.MaxPooling1D(pool_size=3, strides=3)(x)# type: ignore
   
   x = layers.Flatten()(x)# type: ignore

   # 全连接层
   x = layers.Dense(num_classes)(x) # type: ignore
   outputs = layers.Softmax()(x) # type: ignore

   model = models.Model(inputs=inputs, outputs=outputs) # type: ignore
   return model
