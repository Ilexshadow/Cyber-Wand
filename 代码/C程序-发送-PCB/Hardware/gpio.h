#ifndef __GPIO_H
#define __GPIO_H
#include "stm32f10x.h"


#define GPIO_A	0x0000
#define GPIO_B	0x0001
#define GPIO_C	0x0002
#define GPIO_D	0x0003
#define GPIO_E	0x0004



#define  LED_H	  	GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define  LED_L	  GPIO_ResetBits(GPIOC,GPIO_Pin_13)

#define	 LED_F			GPIOC->ODR^=GPIO_Pin_13


#define  PA1_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define  PA2_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define  PA3_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_3)
#define  PA4_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define  PA5_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define  PA6_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_6)
#define  PA7_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define  PA8_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define  PA9_ON	  		GPIO_SetBits(GPIOA,GPIO_Pin_9)
#define  PA10_ON	  	GPIO_SetBits(GPIOA,GPIO_Pin_10)
#define  PA11_ON	  	GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define  PA12_ON	  	GPIO_SetBits(GPIOA,GPIO_Pin_12)
#define  PA13_ON	  	GPIO_SetBits(GPIOA,GPIO_Pin_13)
#define  PA14_ON	  	GPIO_SetBits(GPIOA,GPIO_Pin_14)
#define  PA15_ON	  	GPIO_SetBits(GPIOA,GPIO_Pin_15)

#define  PB0_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define  PB1_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_1)
#define  PB2_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_2)
#define  PB3_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_3)
#define  PB4_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_4)
#define  PB5_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define  PB6_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define  PB7_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define  PB8_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define  PB9_ON	  		GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define  PB10_ON	  	GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define  PB11_ON	  	GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define  PB12_ON	  	GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define  PB13_ON	  	GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define  PB14_ON	  	GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define  PB15_ON	  	GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define  PC14_ON	  	GPIO_SetBits(GPIOC,GPIO_Pin_14)
#define  PC15_ON	  	GPIO_SetBits(GPIOC,GPIO_Pin_15)



#define  PA1_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define  PA2_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define  PA3_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define  PA4_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define  PA5_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define  PA6_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define  PA7_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define  PA8_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define  PA9_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_9)
#define  PA10_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_10)
#define  PA11_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define  PA12_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_12)
#define  PA13_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_13)
#define  PA14_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_14)
#define  PA15_OFF	  	GPIO_ResetBits(GPIOA,GPIO_Pin_15)


#define  PB0_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define  PB1_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define  PB2_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define  PB3_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_3)
#define  PB4_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_4)
#define  PB5_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define  PB6_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_6)
#define  PB7_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define  PB8_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define  PB9_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define  PB10_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define  PB11_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define  PB12_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define  PB13_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define  PB14_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define  PB15_OFF	  	GPIO_ResetBits(GPIOB,GPIO_Pin_15)

#define  PC14_OFF	  	GPIO_ResetBits(GPIOC,GPIO_Pin_14)
#define  PC15_OFF	  	GPIO_ResetBits(GPIOC,GPIO_Pin_15)




#define  READ_A0			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//A0
#define  READ_A1			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)//A1
#define  READ_A2			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)//A2
#define  READ_A3			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//A3
#define  READ_A4			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//A4
#define  READ_A5			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//A5
#define  READ_A6			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//A6
#define  READ_A7			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A7
#define  READ_A8			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A8
#define  READ_A9			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A9
#define  READ_A10			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A10
#define  READ_A11			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A11
#define  READ_A12			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A12
#define  READ_A13			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A13
#define  READ_A14			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A14
#define  READ_A15			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//A15


#define  READ_B0			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//B0
#define  READ_B1			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)//B1
#define  READ_B2			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)//B2
#define  READ_B3			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3)//B3
#define  READ_B4			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)//B4
#define  READ_B5			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//B5
#define  READ_B6			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//B6
#define  READ_B7			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//B7
#define  READ_B8			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)//B8
#define  READ_B9			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)//B9
#define  READ_B10			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//B10
#define  READ_B11			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//B11
#define  READ_B12			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//B12
#define  READ_B13			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//B13
#define  READ_B14			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//B14
#define  READ_B15			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//B15


#define  READ_C14			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)//C14
#define  READ_C15			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)//C15


void GPIO_init(u16 GPIOx, u16 GPIO_Pin, u8 mode);




#endif 
