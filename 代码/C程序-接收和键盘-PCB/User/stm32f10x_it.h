/*******************************************************************************
** 版权:		利尔达科技有限公司
** 文件名: 		stm32f10x_it.h
** 版本：  		1.0
** 工作环境: 	RealView MDK-ARM 4.14
** 作者: 		wuguoyan
** 生成日期: 	2011-04-14
** 功能:		相关的中断服务函数
** 相关文件:	stm32f10x_it.c  ,stm32f10x.h
** 修改日志：	2011-03-23   创建文档
** 版权所有     (C)2005-2011 利尔达科技有限公司
*******************************************************************************/

#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

/* 包含的头文件---------------------------------------------------------------*/
#include "stm32f10x.h"

/* 类型定义 ------------------------------------------------------------------*/
/* 常量定义 ------------------------------------------------------------------*/
/* 宏定义 --------------------------------------------------------------------*/
/* 函数定义------------------------------------------------------------------ */

void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);
void USB_LP_CAN1_RX0_IRQHandler(void);

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2011 Lierda ****************END OF FILE****/
