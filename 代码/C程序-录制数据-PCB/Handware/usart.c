#include "stm32f10x.h"
#include "usart.h"



//USART1
unsigned char USART1_race_buf[30];
unsigned char USART1_count = 0;
unsigned char usart1_race_start_bit = 0;
unsigned char usart1_race_time_count = 0;
unsigned char usart1_race_over_bit = 0;
unsigned char usart1_race_time = 0;



//USART2
unsigned char USART2_race_buf[30];
unsigned char USART2_count = 0;
unsigned char usart2_race_start_bit = 0;
unsigned char usart2_race_time_count = 0;
unsigned char usart2_race_over_bit = 0;
unsigned char usart2_race_time = 0;


void USART1_config(unsigned int BaudRate)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef     USART_InitStructure;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;       
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
	USART_Cmd(USART1, ENABLE);
	

	USART_InitStructure.USART_BaudRate= BaudRate;   
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;   
	USART_InitStructure.USART_Parity= USART_Parity_No ;     
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Rx |USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}


void USART2_config(unsigned int BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    /* Enable the USART2 Pins Software Remapping */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); 
    
    
    /* Configure USART2 Rx (PA.03) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART2 Tx (PA.02) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);    
    
    USART_InitStructure.USART_BaudRate = BaudRate; 
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1; 
    USART_InitStructure.USART_Parity = USART_Parity_No; 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	  
    
    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    //USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
    /* Enable USART2 */
    USART_Cmd(USART2, ENABLE);
}




void USART1_IRQHandler(void)
{  
	unsigned char temp = 0;
  
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{  
		temp=USART_ReceiveData(USART1);
    USART_ClearFlag(USART1,USART_FLAG_RXNE); 
  }  
  else  
  {  
		USART_ClearFlag(USART1,USART_FLAG_TC);  
  }  
} 



void USART2_IRQHandler(void)
{
	unsigned char temp=0;
	
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
	{  
		temp=USART_ReceiveData(USART2);
		USART_ClearFlag(USART2,USART_FLAG_RXNE);
	}  
	else  
	{  
		USART_ClearFlag(USART2,USART_FLAG_TC);  
	}
}



void USART1_send_all(unsigned char *byte,unsigned char send_mun)
{
	unsigned char i;

	for(i=0;i<send_mun;i++)
	{
		USART_SendData(USART1,*byte);
		byte++;
		
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
	}
}



void USART2_send_all(unsigned char *byte,unsigned char send_mun)
{
	unsigned char i;

	for(i=0;i<send_mun;i++)
	{
		USART_SendData(USART2,*byte);
		byte++;
		
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	}
}









