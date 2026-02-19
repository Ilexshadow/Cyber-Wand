#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//SCL接B10，SDA接B11 原来
//SCL接B6，SDA接B7 现在

void MyI2C_W_SCL(uint8_t BitValue)
{
	//GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
	GPIO_WriteBit(GPIOB,GPIO_Pin_6,(BitAction)BitValue);
	Delay_us(10);		//延时10us，防止时序频率超过要求
}

void MyI2C_W_SDA(uint8_t BitValue)
{
	//GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
	GPIO_WriteBit(GPIOB,GPIO_Pin_7,(BitAction)BitValue);
	Delay_us(10);		//延时10us，防止时序频率超过要求
}

uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	//BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);
	Delay_us(10);		//延时10us，防止时序频率超过要求
	return BitValue;
}

void MyI2C_Init(void)//I2C初始化
{
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;		//开漏输出模式
	//GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11	;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7	;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	//GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11 );		//开始时SCL和SDA处于高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7 );		//开始时SCL和SDA处于高电平
}

void MyI2C_Start(void)
{	
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);		//其他所有单元都保证SCL以低电平结束，以方便各个单元的拼接
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);		//只有终止单元保证SCL以高电平结束
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	MyI2C_W_SDA(Byte & 0x80);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
	MyI2C_W_SDA(Byte & 0x40);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
	MyI2C_W_SDA(Byte & 0x20);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
	MyI2C_W_SDA(Byte & 0x10);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
	MyI2C_W_SDA(Byte & 0x08);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
	MyI2C_W_SDA(Byte & 0x04);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
	MyI2C_W_SDA(Byte & 0x02);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
	
	MyI2C_W_SDA(Byte & 0x01);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t Byte = 0x00;
	MyI2C_W_SDA(1);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x80;
	MyI2C_W_SCL(0);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x40;
	MyI2C_W_SCL(0);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x20;
	MyI2C_W_SCL(0);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x10;
	MyI2C_W_SCL(0);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x08;
	MyI2C_W_SCL(0);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x04;
	MyI2C_W_SCL(0);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x02;
	MyI2C_W_SCL(0);
	
	MyI2C_W_SCL(1);
	if(MyI2C_R_SDA() == 1) Byte = Byte | 0x01;
	MyI2C_W_SCL(0);
	
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}
