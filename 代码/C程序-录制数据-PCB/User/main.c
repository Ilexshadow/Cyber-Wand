#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MPU6050.h"
#include "usart.h"
#include "stdio.h"


int16_t AX, AY, AZ, GX, GY, GZ;
uint8_t Key_Old = 1;
uint8_t Key_New = 1;
uint8_t motion_index = 0;
uint8_t isRecording = 0;

//重定向c库函数printf到串口，重定向后可使用printf函数  需要设置一下  在target 中 USE Micro Lib 打钩 才能用  在上面添加   #include "stdio.h"
int fputc(int ch, FILE *f)//有个问题  函数没有声明  也可以用 
{
	/* 发送一个字节数据到串口 */
	USART_SendData(USART1, (uint8_t) ch);
		
	/* 等待发送完毕 */
	while (!(USART1->SR & USART_FLAG_TXE));
	return ch;
}

void Key_Init(void)//初始化按钮A6
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}


int main(void)
{
	MPU6050_Init();
	Key_Init();
	USART1_config(115200);//串口1初始化  用于串口打印调试
	printf("uart1_ok\n");//打印一个字符串
	
	while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		Key_Old = Key_New;
		Key_New = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
		if(Key_Old == 1 && Key_New == 0)//如果按钮被按下
		{
			if(!isRecording)
			{
				isRecording = 1;
				printf("Start\n");
			}
		}
		if(isRecording)//如果在录制
		{
			printf("%d,%d,%d,%d,%d,%d\n",AX,AY,AZ,GX,GY,GZ);
			motion_index ++;
			if(motion_index >= 100)
			{
				motion_index = 0;
				isRecording = 0;
				printf("End\n");
			}
		}
	}
}
