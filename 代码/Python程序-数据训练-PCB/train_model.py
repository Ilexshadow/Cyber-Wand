import tensorflow as tf
import matplotlib.pyplot as plt

def train_model(model,
                X_train_scaled, y_train,
                X_test_scaled, y_test,
                epochs=100, batch_size=16):
    
    model.compile(
        optimizer='adam', 
        loss='categorical_crossentropy', 
        metrics=['accuracy'])
    
    model.summary()
    
    history = model.fit(
        X_train_scaled, y_train,
        epochs=epochs,
        batch_size=batch_size,
        validation_data=(X_test_scaled, y_test),
        callbacks=[
            tf.keras.callbacks.EarlyStopping(patience=8, restore_best_weights=True),
            tf.keras.callbacks.ReduceLROnPlateau(patience=4, factor=0.5, verbose=1)
        ]
    )

    # 绘制loss曲线
    plot_loss_curves(history)

    return history

def plot_loss_curves(history):
    """绘制训练和验证的loss曲线"""
    # 获取训练和验证的loss值
    train_loss = history.history['loss']
    val_loss = history.history['val_loss']
    
    # 获取训练和验证的准确率
    train_acc = history.history['accuracy']
    val_acc = history.history['val_accuracy']
    
    # 创建图表
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
    
    # 绘制loss曲线
    epochs_range = range(1, len(train_loss) + 1)
    ax1.plot(epochs_range, train_loss, label='Training Loss')
    ax1.plot(epochs_range, val_loss, label='Validation Loss')
    ax1.set_title('Training and Validation Loss')
    ax1.set_xlabel('Epochs')
    ax1.set_ylabel('Loss')
    ax1.legend()
    ax1.grid(True)
    
    # 绘制准确率曲线
    ax2.plot(epochs_range, train_acc, label='Training Accuracy')
    ax2.plot(epochs_range, val_acc, label='Validation Accuracy')
    ax2.set_title('Training and Validation Accuracy')
    ax2.set_xlabel('Epochs')
    ax2.set_ylabel('Accuracy')
    ax2.legend()
    ax2.grid(True)
    
    plt.tight_layout()
    plt.savefig('training_curves.png', dpi=300, bbox_inches='tight')
    plt.show()