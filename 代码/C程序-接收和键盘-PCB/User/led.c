#include "led.h"

void Led_configuration(void)			//设置系统时钟
{
	GPIO_InitTypeDef gpio;				//初始化结构体，设置GPIO接口
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);		// 打开时钟
	
	gpio.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;		//最大翻转频率为50Hz
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;		//设置GPIO8和GPIO9为推挽输出
	GPIO_Init(GPIOF,&gpio);
	
	LED1_OFF();
	LED2_OFF();
	LED3_OFF();
	LED4_OFF();
}

void LED_State(u8 LEDNumber,LEDStatus NewStatus)
{
	assert_param(LEDNumber(Number));
	assert_param(LED_STATE(NewStatus));
	
	switch(LEDNumber)
	{
		case LED1 :
			if (NewStatus==OFF)	LED1_OFF();
				else LED1_ON();
			break;
		case LED2 :
			if (NewStatus==OFF)	LED2_OFF();
				else LED2_ON();
			break;
		case LED3 :
			if (NewStatus==OFF)	LED3_OFF();
				else LED3_ON();
			break;
		case LED4 :
			if (NewStatus==OFF)	LED4_OFF();
				else LED4_ON();
			break;
		default:
			break;
	}
}
