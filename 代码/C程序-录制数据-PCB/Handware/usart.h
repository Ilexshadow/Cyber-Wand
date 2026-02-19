#ifndef __UART_H
#define __UART_H


void USART1_config(unsigned int BaudRate);
void USART2_config(unsigned int BaudRate);
void USART1_send_nack(void);
void USART1_send_all(unsigned char *byte,unsigned char send_mun);
void USART2_send_all(unsigned char *byte,unsigned char send_mun);



#endif 
