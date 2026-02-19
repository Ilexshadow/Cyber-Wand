#ifndef _MPU6050_H
#define _MPU6050_H

void MPU6050_Init(void);
void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data);		//指定地址写一个Byte
uint16_t MPU6050_ReadReg(uint8_t RegAddress);		//指定地址读一个Byte
void MPU6050_GetData(int16_t *Accx, int16_t *Accy, int16_t *Accz, int16_t *Gyrox, int16_t *Gyroy, int16_t *Gyroz);		//读取数据
uint8_t MPU6050_GetID(void);

#endif

