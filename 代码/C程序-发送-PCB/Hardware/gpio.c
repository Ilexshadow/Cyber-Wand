#include "stm32f10x.h"
#include "gpio.h"




void GPIO_init(u16 GPIOx, u16 GPIO_Pin, u8 mode)
{
	GPIO_InitTypeDef        GPIO_InitStructure;

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









