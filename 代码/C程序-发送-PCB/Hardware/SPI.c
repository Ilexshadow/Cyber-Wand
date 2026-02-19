#include "stm32f10x.h"
#include "spi.h"





void SPI1_write_byte(unsigned char addr,unsigned char buffer) 
{
	SPI1_NSS_L;
	spi1_send_byte_fun(addr);
	spi1_send_byte_fun(buffer);
	SPI1_NSS_H; 
}

unsigned char  SPI1_read_byte(unsigned char addr)
{
	unsigned char Value;
	SPI1_NSS_L;
	spi1_send_byte_fun(addr);
	Value = spi1_send_byte_fun(0x00);
	SPI1_NSS_H;

	return Value;
}


u8 spi1_send_byte_fun(u8 byte)//发送和接收都是这个
{
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET)//发送是空
	{}
	SPI_I2S_SendData(SPI1, byte); // 向从机发送数据 
	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET)//接收是空
	{}
		
	return SPI_I2S_ReceiveData(SPI1);//读数据 
}





void SPI1_Init_fun(void)  //spi时序  SPI_CPOL   SPI_CPHA    速率 SPI_BaudRatePrescaler_256 
{  
  SPI_InitTypeDef  SPI_InitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;  
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); 
  
	
	//NSS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	//CLK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	//MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  	//全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 												//主模式 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;  										//每次8bit  还是 16bit
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; 														//时钟参数 要求平时为低
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  												//时钟参数 第一个沿
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;  														//硬件模式（SPI_NSS_Hard）与软件模式（SPI_NSS_Soft）
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  	//本成员设置波特率分频值
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  									//MSB 先行（高位数据在前）还是 LSB先行（低位数据在前）
  SPI_InitStructure.SPI_CRCPolynomial = 7;  														//不用CRC
  SPI_Init(SPI2, &SPI_InitStructure);  
  
  SPI_Cmd(SPI2, ENABLE); 
	
	SPI1_NSS_H;
} 



void SPI2_Init_fun(void)  //spi时序  SPI_CPOL   SPI_CPHA    速率 SPI_BaudRatePrescaler_256 
{  
  SPI_InitTypeDef  SPI_InitStructure;  
  GPIO_InitTypeDef GPIO_InitStructure;  

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  
	

	//NSS
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	
	//CLK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
	//MISO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;  						
  //SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; 												
  //SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  


	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	

  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;													
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32; //不能时间太长，256是不行的
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  								
  SPI_InitStructure.SPI_CRCPolynomial = 7;  													
  SPI_Init(SPI2, &SPI_InitStructure);  

  SPI_Cmd(SPI2, ENABLE); 
	
	SPI2_NSS_H;
} 





u8 spi2_send_byte_fun(u8 byte)			//发送和接收都是这个
{
	while (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET)//发送是空
	{}
	SPI_I2S_SendData(SPI2, byte); // 向从机发送数据 
	while (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET)//接收是空
	{}
		
	return SPI_I2S_ReceiveData(SPI2);//读数据 
}



/*
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
		{
		retry++;
		if(retry>200)return 0;
		}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
		{
		retry++;
		if(retry>200)return 0;
		}	  						    
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
}
*/





