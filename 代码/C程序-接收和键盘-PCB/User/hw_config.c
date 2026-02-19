#include "stm32f10x.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"

//定义使用外部晶振  ,如果不定义就使用内部的HSI高速RC震荡
#define USB_HSE_AS_SYS_CLOCK

#define USB_DISCONNECT                      GPIOG
#define USB_DISCONNECT_PIN                  GPIO_Pin_11

//本开发板只用了 PA.0，PC.13模拟鼠标动作
#define GPIO_Pin_up                         GPIO_Pin_8  /* PA.8 */
#define GPIO_Pin_down                       GPIO_Pin_3 /* PD.3 */
#define GPIO_Pin_right                      GPIO_Pin_0  /* PA.0 */
#define GPIO_Pin_left                       GPIO_Pin_13  /* PC.13 */

#define RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOG
//#define GPIO_RIGHT                          GPIOC
//#define GPIO_LEFT                           GPIOC
// #define GPIO_DOWN                           GPIOB
// #define GPIO_UP                             GPIOB
#define GPIO_Click_left                     GPIOC
#define GPIO_Click_right                    GPIOA
#define GPIO_Click_up                    		GPIOA
#define GPIO_Click_down	                   	GPIOD

//#define GPIO_KEY                            GPIOB
#define RCC_APB2Periph_ALLGPIO                 (RCC_APB2Periph_GPIOA \
                                              | RCC_APB2Periph_GPIOB \
                                              | RCC_APB2Periph_GPIOC \
                                              | RCC_APB2Periph_GPIOD \
                                              | RCC_APB2Periph_GPIOE )
/* 变量声明------------------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
EXTI_InitTypeDef EXTI_InitStructure;

/*******************************************************************************
  * @函数名称	RCC_HSI_Configuration
  * @函数说明   配置使用内部的HSI作为系统时钟源
  * @输入参数   无
  * @输出参数   无
  * @返回参数   无
*******************************************************************************/
void RCC_HSI_Configuration(void)
{
    RCC_DeInit();
    //使能HSI
    RCC_HSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
    {
    }        //等待HSI准备好
    //使能Falsh 的预取
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    //设置Falsh等待一个周期
    FLASH_SetLatency(FLASH_Latency_1);
    // 设置HCLK = SYSCLK 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    //设置 PCLK2 = HCLK 
    RCC_PCLK2Config(RCC_HCLK_Div1);
    // PCLK1 = HCLK/2 
    RCC_PCLK1Config(RCC_HCLK_Div2);
    //设置 PLLCLK = 8MHz * 6 = 48 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_12);
    //使能 PLL 
    RCC_PLLCmd(ENABLE);
    //等待PLL稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }
    //选取PLL作为系统时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //等待PLL选为系统时钟
    while (RCC_GetSYSCLKSource() != 0x08)
    {
    }
}

/*******************************************************************************
  * @函数名称	Set_System
  * @函数说明   配置系统时钟
  * @输入参数   无
  * @输出参数	无
  * @返回参数   无
*******************************************************************************/



void Set_System(void)
{
    //GPIO_InitTypeDef GPIO_InitStructure;

    //配置系统时钟，初始化Falsh接口，初始化PLL
    
	
	
	
	
	/*
#ifdef USB_HSE_AS_SYS_CLOCK    //如果使用外部晶振就用这个函数
    SystemInit();
#else
    //如果使用内部RC晶振作为时钟源就需要配置
    RCC_HSI_Configuration();
#endif
	*/
	
	RCC_HSI_Configuration();
	
	
	/*
    //设置所有引脚为输入
    GPIO_AINConfig();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);


    //配置 USB_DISCONNECT引脚为上拉
    GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);

	
    //使能鼠标按键的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);

    //配置按键的IO
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_right;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIO_Click_right, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_left;
    GPIO_Init(GPIO_Click_left, &GPIO_InitStructure);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_up;
    GPIO_Init(GPIO_Click_up, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_down;
    GPIO_Init(GPIO_Click_down, &GPIO_InitStructure);
		*/
}

/*******************************************************************************
  * @函数名称	Set_USBClock
  * @函数说明   配置USB系统时钟
  * @输入参数   无
  * @输出参数	无
  * @返回参数   无
*******************************************************************************/
void Set_USBClock(void)
{
	
    //配置USB时钟
#ifdef USB_HSE_AS_SYS_CLOCK    //如果使用外部晶振就用这个函数
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
#else
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
#endif
    // 使能USB时钟 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
	
	
	
	
	//RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_Div1);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
  * @函数名称	GPIO_AINConfig
  * @函数说明   配置所有的IO为输入模式，减少功耗
  * @输入参数   无
  * @输出参数	无
  * @返回参数   无
*******************************************************************************/
void GPIO_AINConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    //使能所有时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALLGPIO, ENABLE);

    //配置所有的IO为模拟输入模式 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    // 关闭所有时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALLGPIO, DISABLE);
}

/*******************************************************************************
  * @函数名称	USB_Interrupts_Config
  * @函数说明   配置USB中断
  * @输入参数   无
  * @输出参数	无
  * @返回参数   无
*******************************************************************************/
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    //使用第二组中断
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    //使能USB中断
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
  * @函数名称	USB_Cable_Config
  * @函数说明   软件连接/不连接USB线
  * @输入参数   NewState：新状态
  * @输出参数	无
  * @返回参数   无
*******************************************************************************/
void USB_Cable_Config (FunctionalState NewState)
{
    if (NewState == DISABLE)
    {
        GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }
    else
    {
        GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }
}

/*******************************************************************************
  * @函数名称	JoyState
  * @函数说明   解析按键的方向
  * @输入参数   无
  * @输出参数	无
  * @返回参数   按键方向值
*******************************************************************************/
uint8_t JoyState(void)
{
    // 鼠标左移的按键按下
    if (!GPIO_ReadInputDataBit(GPIO_Click_left, GPIO_Pin_left))
    {
			  return LEFT;
    }
    // 鼠标右移的按键按下
    if (!GPIO_ReadInputDataBit(GPIO_Click_right, GPIO_Pin_right))
    {
			  return  RIGHT;
    }
		// 鼠标上移的按键按下
    if (!GPIO_ReadInputDataBit(GPIO_Click_up, GPIO_Pin_up))
    {
			  return  UP;
    }
		// 鼠标下移的按键按下
    if (!GPIO_ReadInputDataBit(GPIO_Click_down, GPIO_Pin_down))
    {
			  return  DOWN;
    }
		
// 		if (!GPIO_ReadInputDataBit(GPIOD, JOY_SEL))
// 		{
// 			return SEL;
// 		}
// 		if (!GPIO_ReadInputDataBit(GPIOD, MISE_LEFT))
// 		{
// 			return LEFT_CLICK;
// 		}
// 		if (!GPIO_ReadInputDataBit(GPIOD, MISE_RIGHT))
// 		{
// 			return  RIGHT_CLICK;
// 		}
//     else
    {
        return 0;
    }
}

/*******************************************************************************
  * @函数名称	Joystick_Send
  * @函数说明   将包含按键事件信息的内容存入发送缓冲区发送
  * @输入参数   Keys：获得的按键信息
  * @输出参数	无
  * @返回参数   无
*******************************************************************************/
void Joystick_Send(uint8_t Keys)
{
	  uint16_t i;
    uint8_t Mouse_Buffer[4] = {0, 0, 0, 0};  //第四个字节代表滚轮上移还是下移
    int8_t X = 0, Y = 0;
		Keys = JoyState();
    switch (Keys)
    {
    case LEFT:
        X -= CURSOR_STEP;
        break;
    case RIGHT:

        X += CURSOR_STEP;
        break;
    case UP:
        Y -= CURSOR_STEP;
        break;
    case DOWN:
        Y += CURSOR_STEP;
        break;
		case  SEL:
           //  Sel_flag=1;
                 break;
          //鼠标发送的有用数据是4个字节,0字节的bit0表示鼠标左键单击,bit1是右键
    case  LEFT_CLICK:
          Mouse_Buffer[0] =0x01; //上面说了,鼠标发送的4个字节的0号字节有左右键信息.
           break;
    case  RIGHT_CLICK:
           Mouse_Buffer[0]=0x02;  //Mouse_Buffer[0]=0x03代表中键
           break;
    default: 
           return;


    }
   
    // 填充发送的数据 
     Mouse_Buffer[1] = X;
     Mouse_Buffer[2] = Y;                                    
    //把鼠标坐标的值复制到端点1的发送内存区域
    UserToPMABufferCopy(Mouse_Buffer, GetEPTxAddr(ENDP1), 4);
		for(i=10000;i>0;i--);  //延时
		 Mouse_Buffer[0] =0x00;   //因为前面已经发送了，电脑会一直认为有键按下而且没有释放，所以发送 Mouse_Buffer[0] =0x00;代表释放按键
		 UserToPMABufferCopy(Mouse_Buffer, GetEPTxAddr(ENDP1), 4);
    //使能端点1的发送
    SetEPTxValid(ENDP1);
}

/*******************************************************************************
  * @函数名称	Get_SerialNum
  * @函数说明   获得设备描述符
  * @输入参数   无
  * @输出参数	无
  * @返回参数   无
*******************************************************************************/
void Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

    Device_Serial0 = *(uint32_t*)(0x1FFFF7E8);
    Device_Serial1 = *(uint32_t*)(0x1FFFF7EC);
    Device_Serial2 = *(uint32_t*)(0x1FFFF7F0);

    if (Device_Serial0 != 0)
    {
        Joystick_StringSerial[2] = (uint8_t)(Device_Serial0 & 0x000000FF);
        Joystick_StringSerial[4] = (uint8_t)((Device_Serial0 & 0x0000FF00) >> 8);
        Joystick_StringSerial[6] = (uint8_t)((Device_Serial0 & 0x00FF0000) >> 16);
        Joystick_StringSerial[8] = (uint8_t)((Device_Serial0 & 0xFF000000) >> 24);

        Joystick_StringSerial[10] = (uint8_t)(Device_Serial1 & 0x000000FF);
        Joystick_StringSerial[12] = (uint8_t)((Device_Serial1 & 0x0000FF00) >> 8);
        Joystick_StringSerial[14] = (uint8_t)((Device_Serial1 & 0x00FF0000) >> 16);
        Joystick_StringSerial[16] = (uint8_t)((Device_Serial1 & 0xFF000000) >> 24);

        Joystick_StringSerial[18] = (uint8_t)(Device_Serial2 & 0x000000FF);
        Joystick_StringSerial[20] = (uint8_t)((Device_Serial2 & 0x0000FF00) >> 8);
        Joystick_StringSerial[22] = (uint8_t)((Device_Serial2 & 0x00FF0000) >> 16);
        Joystick_StringSerial[24] = (uint8_t)((Device_Serial2 & 0xFF000000) >> 24);
    }
}



