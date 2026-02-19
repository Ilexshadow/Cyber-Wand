/*******************************************************************************
** 版权:		利尔达科技有限公司
** 文件名: 		hw_config.h
** 版本：  		1.0
** 工作环境: 	RealView MDK-ARM 4.14
** 作者: 		吴国炎
** 生成日期: 	2011-04-14
** 功能:		硬件平台的相关配置
** 相关文件:	usb_type.h，hw_config.c
** 修改日志：	2011-04-14   创建文档
** 版权所有     (C)2005-2011 利尔达科技有限公司
*******************************************************************************/
/* 防止重定义 ----------------------------------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* 包含的头文件 --------------------------------------------------------------*/
#include "usb_type.h"
/* 宏定义 --------------------------------------------------------------------*/
#define DOWN            1
#define LEFT            2
#define RIGHT           3
#define UP              4
#define CURSOR_STEP     3

#define SEL    7
//#define CURSOR_STEP   5  //原来的版本是30 ,被我改成5 这样每次移动时鼠标更准确
#define LEFT_CLICK      8  //这两个是我加的 ,把板子上的KEY2和KEY3作为左键和右键
#define RIGHT_CLICK     9

/* 函数声明 ----------------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);
void GPIO_AINConfig(void);
void USB_Interrupts_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void Joystick_Send(uint8_t Keys);
uint8_t JoyState(void);
void Get_SerialNum(void);
void RCC_HSI_Configuration(void);

#endif  /*__HW_CONFIG_H*/


/******************* (C) COPYRIGHT 2011 Lierda *****************文件结束*******/
