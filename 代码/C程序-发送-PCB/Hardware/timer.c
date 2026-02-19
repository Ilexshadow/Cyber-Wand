#include "stm32f10x.h"
#include "timer.h"
#include "gpio.h"




extern unsigned char usart1_race_start_bit;
extern unsigned char usart1_race_time_count;
extern unsigned char usart1_race_over_bit;
extern unsigned char usart1_race_time;
extern unsigned char USART1_count;


extern unsigned char usart2_race_start_bit;
extern unsigned char usart2_race_time_count;
extern unsigned char usart2_race_over_bit;
extern unsigned char usart2_race_time;
extern unsigned char USART2_count;


void Timer_Config(void)         //1ms
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;  
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);  			//使能T2
	TIM_DeInit(TIM2);                              							//复位T2   
	TIM_TimeBaseStructure.TIM_Period=3000;          							//定时器周期    10000 = 1ms   1=2us    10000=10ms			100000=32ms
	TIM_TimeBaseStructure.TIM_Prescaler=72-1;     							//预分频数===========================72 = 1ms中断
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;   		//TIM2时钟分频 1表示不分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		//向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);     
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);           						//清益处标志
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);      							//使能中断
	TIM_Cmd(TIM2, ENABLE);                       								//使能
	
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);           	//优先组设置
	NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn ;           	//TIM2中断选通
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         		//使能中断控制
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler(void)
{   
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET )
	{
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);
		
		
//		GPIOB->ODR^=GPIO_Pin_12;//250ns 跳变一次
		
		if(usart1_race_start_bit==1)
		{
			usart1_race_time++;
			if(usart1_race_time==2)
			{
				usart1_race_over_bit = 1;
				
				usart1_race_start_bit = 0;
				usart1_race_time = 0;
				
				USART1_count = 0;
			}
		}
		
		
		if(usart2_race_start_bit==1)
		{
			usart2_race_time++;
			if(usart2_race_time==2)
			{
				usart2_race_over_bit = 1;
				
				usart2_race_start_bit = 0;
				usart2_race_time = 0;
				
				USART2_count = 0;
				
				GPIOB->ODR^=GPIO_Pin_12;
			}
		}
	}
}
