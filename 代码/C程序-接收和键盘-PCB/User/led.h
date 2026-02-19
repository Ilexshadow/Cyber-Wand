#ifndef _LED_H
#define _LED_H

#include "stm32f10x.h"

#define LED1_ON() 	GPIO_ResetBits(GPIOF,GPIO_Pin_6)
#define LED1_OFF() 	GPIO_SetBits(GPIOF,GPIO_Pin_6)
#define LED2_ON()		GPIO_ResetBits(GPIOF,GPIO_Pin_7)
#define LED2_OFF() 	GPIO_SetBits(GPIOF,GPIO_Pin_7)
#define LED3_ON()		GPIO_ResetBits(GPIOF,GPIO_Pin_8)
#define LED3_OFF() 	GPIO_SetBits(GPIOF,GPIO_Pin_8)
#define LED4_ON() 	GPIO_ResetBits(GPIOF,GPIO_Pin_9)
#define LED4_OFF() 	GPIO_SetBits(GPIOF,GPIO_Pin_9)
#define LED_ALL_ON() 		GPIO_ResetBits(GPIOF,GPIO_Pin_6);GPIO_ResetBits(GPIOF,GPIO_Pin_7);GPIO_ResetBits(GPIOF,GPIO_Pin_8|GPIO_Pin_9)
#define LED_ALL_OFF() 	GPIO_SetBits(GPIOF,GPIO_Pin_6);GPIO_SetBits(GPIOF,GPIO_Pin_7);GPIO_SetBits(GPIOF,GPIO_Pin_8|GPIO_Pin_9)

#define LED1_TOGGLE() 	GPIO_WriteBit(GPIOF,GPIO_Pin_6,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOF,GPIO_Pin_6)))		//电平翻转
#define LED2_TOGGLE() 	GPIO_WriteBit(GPIOF,GPIO_Pin_7,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOF,GPIO_Pin_7)))		//电平翻转
#define LED3_TOGGLE() 	GPIO_WriteBit(GPIOF,GPIO_Pin_8,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOF,GPIO_Pin_8)))		//电平翻转
#define LED4_TOGGLE() 	GPIO_WriteBit(GPIOF,GPIO_Pin_9,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOF,GPIO_Pin_9)))		//电平翻转

#define LED1    ((u8)1)
#define LED2    ((u8)2)
#define LED3    ((u8)3)
#define LED4    ((u8)4)
#define LEDNumber(Number) (((Number)==LED1)||	\
													((Number)==LED2)||	\
													((Number)==LED3)||	\
													((Number)==LED4))
typedef enum {OFF= 0, ON = !OFF} LEDStatus;
#define LED_STATE(STATE) (((STATE) == OFF) || ((STATE) == ON))

void Led_configuration(void);
void LED_State(u8 LEDNumber,LEDStatus NewStatus);

#endif
