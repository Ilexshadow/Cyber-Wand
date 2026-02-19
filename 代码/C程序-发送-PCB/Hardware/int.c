#include "stm32f10x.h"
#include "int.h"


/*
EXTI0 – EXTI4这5个外部中断有着自己的单独的中断响应函数，EXTI5-9共用一个中断响应函数，EXTI10-15共用一个中断响应函数。

1.       设置好相应的时钟；
2.       设置相应的中断；
3.       IO口初始化；
4.       把相应的IO口设置为中断线路（要在设置外部中断之前）并初始化；
5.       在选择的中断通道的响应函数中中断函数。


*/


void NVIC_cfg(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                          //选择中断分组2
        
      
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;     //选择中断通道2
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //响应式中断优先级设置为0
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                   //使能中断
  NVIC_Init(&NVIC_InitStructure);
 
        
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;            //选择中断通道3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //抢占式中断优先级设置为1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //响应式中断优先级设置为1
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                   //使能中断
  NVIC_Init(&NVIC_InitStructure);

        
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;  //选择中断通道5
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占式中断优先级设置为2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //响应式中断优先级设置为2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                   //使能中断
  NVIC_Init(&NVIC_InitStructure);
}

void EXTI_cfg(void)
{
       EXTI_InitTypeDef EXTI_InitStructure;
       //清空中断标志
       EXTI_ClearITPendingBit(EXTI_Line0);
       EXTI_ClearITPendingBit(EXTI_Line1);
       EXTI_ClearITPendingBit(EXTI_Line4);
 
       //选择中断管脚PC.2 PC.3 PC.5
       GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
       GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
       GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
 
       EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1 | EXTI_Line4; //选择中断线路2 3 5
       EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; //设置为中断请求，非事件请求
       EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //设置中断触发方式为上下降沿触发
       EXTI_InitStructure.EXTI_LineCmd = ENABLE;                                          //外部中断使能
      EXTI_Init(&EXTI_InitStructure);
}


void EXTI0_IRQHandler(void)//A0
{
       //清空中断标志位，防止持续进入中断
       EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)//A1
{
       EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI4_IRQHandler(void)//A4
{

       EXTI_ClearITPendingBit(EXTI_Line4);
}


