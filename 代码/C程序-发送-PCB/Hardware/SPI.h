#ifndef __SPI_H
#define __SPI_H
#include "stm32f10x.h"


#define SPI1_NSS_L			GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define SPI1_NSS_H			GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define SPI2_NSS_L			GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define SPI2_NSS_H			GPIO_SetBits(GPIOB,GPIO_Pin_12)


void SPI1_Init_fun(void);
void SPI2_Init_fun(void);


unsigned char  SPI1_read_byte(unsigned char addr);
void SPI1_write_byte(unsigned char addr,unsigned char buffer);
u8 spi1_send_byte_fun(u8 byte);



u8 spi2_send_byte_fun(u8 byte);






#endif 


