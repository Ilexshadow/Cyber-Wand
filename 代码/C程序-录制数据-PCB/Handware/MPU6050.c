#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_Address 	0xD0		//110 1000 0

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)		//指定地址写一个Byte
{
	MyI2C_Start();
	
	MyI2C_SendByte(MPU6050_Address);
	MyI2C_ReceiveAck();
	
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_SendByte(Data);
	MyI2C_ReceiveAck();
	
	MyI2C_Stop();
}

uint16_t MPU6050_ReadReg(uint8_t RegAddress)		//指定地址读一个Byte
{
	uint16_t Data;
	
	MyI2C_Start();
	
	MyI2C_SendByte(MPU6050_Address);
	MyI2C_ReceiveAck();
	
	MyI2C_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_Address | 0x01);
	MyI2C_ReceiveAck();
	
	Data = MyI2C_ReceiveByte();
	MyI2C_SendAck(1);
	
	MyI2C_Stop();
	return Data;
}

void MPU6050_Init(void)
{
	MyI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);		//解除睡眠，选择陀螺仪时钟
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x00);		//6个轴都不待机
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);		//采样分频为10
	MPU6050_WriteReg(MPU6050_CONFIG,0x06);		//滤波参数最大
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);		//陀螺仪最大量程
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);		//加速度计最大量程
}

uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *Accx, int16_t *Accy, int16_t *Accz, 
											int16_t *Gyrox, int16_t *Gyroy, int16_t *Gyroz)		//读取数据
{
	uint16_t DataH,DataL;
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*Accx = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*Accy = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*Accz = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*Gyrox = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*Gyroy = (DataH << 8) | DataL;
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*Gyroz = (DataH << 8) | DataL;
}
