import sys
import os

from tensorflow.keras import *# type: ignore
from tensorflow.keras.datasets import mnist# type: ignore
from tensorflow.keras.layers import *# type: ignore
from tensorflow.keras.activations import *# type: ignore
from tensorflow.keras.models import load_model, save_model# type: ignore
from tensorflow.keras.utils import to_categorical# type: ignore
import tensorflow as tf
import numpy as np
from nnom import *

from split_data import split_data
from load_data import load_data

def main():
    
    model_dir = 'cyber_wand_model.h5'
    model = load_model(model_dir)

    X,y, label_names = load_data()
    X_train, X_test, y_train_original, y_test_original = split_data(X, y)
    
    # Convert class vectors to binary class matrices.
    y_train = to_categorical(y_train_original, num_classes = len(label_names))
    y_test = to_categorical(y_test_original, num_classes = len(label_names))

    # generate binary dataset for NNoM validation
    generate_test_bin(X_test, y_test, name='test_data.bin')

    # evaluate in Keras (for comparision)
    scores = evaluate_model(model, X_test, y_test)

    cmd = "auto_test.exe"
    os.system(cmd)
    try:
        # get NNoM results
        result = np.genfromtxt('result.csv', delimiter=',', dtype=np.int32, skip_header=1)
        result = result[:,0]        # the first column is the label, the second is the probability
        label = y_test_original[:len(y_test)].flatten()     # use the original numerical label
        acc = np.sum(result == label).astype('float32')/len(result)
        if (acc > 0.5):
            print("Top 1 Accuracy on Keras %.2f%%" %(scores[1]*100))
            print("Top 1 Accuracy on NNoM  %.2f%%" %(acc *100))
            return 0
        # else:
        #     raise Exception('test failed, accuracy is %.1f%% < 80%%' % (acc * 100.0))
    except:
        raise Exception('could not perform the test with NNoM')

if __name__ == "__main__":
    main()
