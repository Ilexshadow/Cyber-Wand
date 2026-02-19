#include "stm32f10x.h"
#include "delay.h"






void delay_us(uint16_t time_ms)
{
  uint16_t i;
	unsigned char j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<6;j++ );//大约1us
  }
}





void delay_ms(uint16_t time_ms)
{
  uint16_t i,j;
  for( i=0;i<time_ms;i++ )
  {
		for( j=0;j<8000;j++ );//大约1ms
  }
}








