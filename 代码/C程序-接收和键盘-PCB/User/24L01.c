#include "stm32f10x.h"
#include "24L01.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_gpio.h"




u8 TX_ADDRESS[5] = {0x34,0x43,0x10,0x10,0x01};//



extern u8 RX_data[8];//2401  接收到的数组



void delay_us( uint16_t time_ms )//大概1us  用示波器测试过
{
  uint16_t i;
	unsigned char j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<6;j++ );//大约1us
  }
}




//单片机的端口初始化函数

void GPIO_init(u16 GPIOx, u16 GPIO_Pin, GPIOMode_TypeDef mode)
{
	
#define GPIO_A	0x0000
#define GPIO_B	0x0001
#define GPIO_C	0x0002
#define GPIO_D	0x0003
#define GPIO_E	0x0004
	
	
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	//使用 PB3和PB4必须加下面三行  A15
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	//完毕

	switch(GPIOx)
	{
		case GPIO_A:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode=mode;
			GPIO_Init(GPIOA,&GPIO_InitStructure);
			break;
		case GPIO_B:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode=mode;
			GPIO_Init(GPIOB,&GPIO_InitStructure);
			break;
		case GPIO_C:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode=mode;
			GPIO_Init(GPIOC,&GPIO_InitStructure);
			break;
		case GPIO_D:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode=mode;
			GPIO_Init(GPIOD,&GPIO_InitStructure);
			break;
		case GPIO_E:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
			GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode=mode;
			GPIO_Init(GPIOE,&GPIO_InitStructure);
			break;
	}
}	





//SPI2  初始化  用于和2401 通讯
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
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; //不能时间太长，256是不行的
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;  								
  SPI_InitStructure.SPI_CRCPolynomial = 7;  													
  SPI_Init(SPI2, &SPI_InitStructure);  

  SPI_Cmd(SPI2, ENABLE); 
	
	//SPI2_NSS_H;
	
	CE_H;
} 



//spi2 发送一个字节
u8 spi2_send_byte_fun(u8 byte)			//发送和接收都是这个
{
	while (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) == RESET)//发送是空
	{}
	SPI_I2S_SendData(SPI2, byte); // 向从机发送数据 
	while (SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) == RESET)//接收是空
	{}
		
	return SPI_I2S_ReceiveData(SPI2);//读数据 
}


//spi2  发送两个字节  第一个是寄存器，第二个是数据
u8 SPI_Write_Reg(u8 Reg,u8 data)
{
	u8 states;

	CSN_L;

	states = spi2_send_byte_fun(Reg);

	states = spi2_send_byte_fun(data);

	CSN_H;
	
	return states;
}



//将2401 设置成接收模式
void RX_2401_init_race(void)
{
	
	GPIO_init(GPIO_C,GPIO_Pin_13,GPIO_Mode_Out_PP);
	LED_H;
	
	
	GPIO_init(GPIO_B,GPIO_Pin_4,GPIO_Mode_IN_FLOATING);//IRQ
	GPIO_init(GPIO_A,GPIO_Pin_8,GPIO_Mode_Out_PP);//CE
	CE_L;
	
	GPIO_init(GPIO_B,GPIO_Pin_12,GPIO_Mode_Out_PP);//CSN
	CSN_H;
	
	
	CE_L;
	
	SPI_Write_Reg(WRITE_REG_24 + EN_AA,0x00);
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + SETUP_RETR,0x00);
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + EN_RXADDR,0x01);
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + RF_CH,1);
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + RX_PW_P0,8);//24
	delay_us(10);
	
	SPI_Write_Reg(WRITE_REG_24 + RF_SETUP,0x07);//2401设置成接收模式
	delay_us(10);
	

	CSN_L;
	delay_us(10);
	spi2_send_byte_fun(WRITE_REG_24 + TX_ADDR);//
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[0]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[1]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[2]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[3]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[4]);
	delay_us(10);
	CSN_H;
	
	
	
	CSN_L;
	delay_us(10);
	spi2_send_byte_fun(WRITE_REG_24 + RX_ADDR_P0);//
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[0]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[1]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[2]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[3]);
	delay_us(10);
	spi2_send_byte_fun(TX_ADDRESS[4]);
	delay_us(10);
	CSN_H;
	
	SPI_Write_Reg(WRITE_REG_24 + CONFIG_24,0x0f);
	delay_us(10);
	
	CE_H;
}




//从2401中  读取收到的8个字节的数据  保存到RX_data数组中
void Read_race_data(void)
{
	u8 i;


	CSN_L;
	delay_us(10);

	spi2_send_byte_fun(RD_RX_PLOAD);
	
	for(i=0;i<8;i++)
	{
		RX_data[i] = spi2_send_byte_fun(0xff);
	}

	CSN_H;
	delay_us(10);
	
}














