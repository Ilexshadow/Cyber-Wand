# 当麻瓜的电子技术遇见巫师的魔法世界 
- 此项目最初想制作一个可以用于游戏[霍格沃茨之遗](https://www.hogwartslegacy.com/en-us)的体感控制器。
- 现在能够做到
  - 通过该项目制作出的魔杖控制角色前后左右移动。
  - 通过挥舞该项目制作出的魔杖，产生特定的键盘输入，从而在游戏中释放特定的魔法。
  
&emsp;&emsp;具体情况可以见  详细介绍ppt  以及  真实游戏展示视频。    

- lyg09270的开源项目[Cyberry_Potter_Electromagic_Wand](https://github.com/lyg09270/Cyberry_Potter_Electromagic_Wand)对此项目有很大的启发作用，向其学习了部分代码和PCB设计，但是最终此项目所使用的Keil版本配置、PCB设计、数据处理与其都有所不同。  
- Keil除版本略新外，配置完全参照[江协科技STM32入门教程](https://www.bilibili.com/video/BV1th411z7sn)。  
- PCB设计使用[嘉立创EDA](https://pro.lceda.cn/)。EDA使用学习了b站up主[Expert电子实验室](https://www.bilibili.com/video/BV1At421h7Ui)的相关教程  
- 使用了majianjia的开源项目[nnom](https://github.com/majianjia/nnom)将Keras神经网络模型变为NNoM神经网络模型，从而可以置于MCU上。

&emsp;&emsp;非常感谢[lyg09270](https://github.com/lyg09270)、[majianjia](https://github.com/majianjia)、[江协科技](https://space.bilibili.com/383400717?spm_id_from=333.788.upinfo.detail.click)、[嘉立创EDA](https://pro.lceda.cn/)等提供的帮助。

 
- 主控芯片：STM32F103C8T6
- 姿态传感器：MPU6050。I2C通信、姿态解算。
- 无线通信：NRF24L01。SPI协议、无线数据传输。
- 电源管理：TP4056。充放电管理。
- PCB设计：嘉立创EDA。
- 软件开发：Keil MDK。

如果这个项目对你有帮助，欢迎点亮⭐
