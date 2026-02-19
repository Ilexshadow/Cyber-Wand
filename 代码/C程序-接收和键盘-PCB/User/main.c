#include "stm32f10x.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "24L01.h"





void Delay(__IO uint32_t nCount);




u8 key_Buf[8] = {0,0,4,0,0,0,0,0};//USB要发送的数据，用于测试用
u8 key_Buf_zero[8] = {0,0,0,0,0,0,0,0};//USB要发送的数据，用于测试用

u8 RX_data[8];//2401 接收到的数据，USB上传，实际是用的这个数组，2401收到什么，USB就发送什么，相当于透传



void Delay_ms( uint16_t time_ms )//真实1ms  用示波器测试过
{
  uint16_t i,j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<8050;j++ );//大约1ms
  }
}




//没有用到，用于测试   就是发送一个按键按下的函数
void send_usb_key_data_fun(void)
{
	UserToPMABufferCopy(key_Buf, GetEPTxAddr(ENDP1), 8);
	SetEPTxValid(ENDP1);
	while(GetEPTxStatus(ENDP1)!=(0x02<<4));
}

//没有用到，用于测试   就是发送8个字节的0   就是没有按键按下
void send_usb_key_zero_data_fun(void)
{
	UserToPMABufferCopy(key_Buf_zero, GetEPTxAddr(ENDP1), 8);
	SetEPTxValid(ENDP1);
	while(GetEPTxStatus(ENDP1)!=(0x02<<4));
}



#define D_TIME	100








//读取2401的   STATUS  寄存器，如果是0x40，就说明收到数据了，然后将收到的8字节，通过USB发送给电脑
void read_fun(void)
{
	u8 read_dat;

	
	read_dat = SPI_Write_Reg(STATUS,0x00);//读2401的 STATUS 寄存器的值
	

	if((read_dat&0x40)==0x40)//如果 STATUS 是0x40  就说明无线收到数据了
	{
		LED_L;//开灯
		SPI_Write_Reg(WRITE_REG_24 + STATUS,read_dat);//清标志位，将读到的数据再重新写这个寄存器就能清楚接收标志

		Read_race_data();//从2401中读取 收到的8个字节
		
		SPI_Write_Reg(WRITE_REG_24 + STATUS,read_dat);////清标志位，将读到的数据再重新写这个寄存器就能清楚接收标志
		

		UserToPMABufferCopy(RX_data, GetEPTxAddr(ENDP1), 8);//将2401收到的RX_data  8个字节  通过USB发送给电脑， 电脑收到后，就会认为有按键按下了
		SetEPTxValid(ENDP1);//发送
		while(GetEPTxStatus(ENDP1)!=(0x02<<4));//判断发送是否完成
		
		LED_H;//关灯
		
		
		//Delay_ms(1);
		
		/*
		UserToPMABufferCopy(key_Buf_zero, GetEPTxAddr(ENDP1), 8);//
		SetEPTxValid(ENDP1);
		while(GetEPTxStatus(ENDP1)!=(0x02<<4));
		*/
		
	}
}

//---------------------------------------------------------------------------------------



#define  USB_H	  		GPIO_SetBits(GPIOA,GPIO_Pin_15)
#define  USB_A8_H	  		GPIO_SetBits(GPIOA,GPIO_Pin_8)





int main(void)
{
  //Set_System();//用不用晶振有修改

	SystemInit();
	Delay_ms(2000);
	
	//GPIO_init(GPIO_A,GPIO_Pin_15,GPIO_Mode_Out_PP);
	//USB_H;

  USB_Interrupts_Config();
  Set_USBClock();//用不用晶振有修改
  USB_Init();
	
	//=====================2401======================================
	SPI2_Init_fun();
	RX_2401_init_race();
	//---------------------------------------------------------------
	
	LED_L;
	Delay_ms(1000);
	LED_H;
	Delay_ms(1000);
	
	while (1)
	{
		/*
		// 在没有无线数据的使用场景下，可以用下面的程序进行测试
		LED_L;
		UserToPMABufferCopy(key_Buf, GetEPTxAddr(ENDP1), 8);
		SetEPTxValid(ENDP1);
		while(GetEPTxStatus(ENDP1)!=(0x02<<4));
		
		Delay_ms(1);
		
		UserToPMABufferCopy(key_Buf_zero, GetEPTxAddr(ENDP1), 8);
		SetEPTxValid(ENDP1);
		while(GetEPTxStatus(ENDP1)!=(0x02<<4));
		
		LED_H;
		
		Delay_ms(1000);
		*/
		
		read_fun();
		//https://www.cnblogs.com/guyandianzi/p/9882644.html
		//按键键值 网址
	}
}




