#ifndef __INT_H
#define __INT_H

#define EXTI0_IRQChannel             ((u8)0x06)  /* EXTI Line0 Interrupt */ 
#define EXTI1_IRQChannel             ((u8)0x07)  /* EXTI Line1 Interrupt */  
#define EXTI2_IRQChannel             ((u8)0x08)  /* EXTI Line2 Interrupt */  
#define EXTI3_IRQChannel             ((u8)0x09)  /* EXTI Line3 Interrupt */  
#define EXTI4_IRQChannel             ((u8)0x0A)  /* EXTI Line4 Interrupt */  


#define EXTI9_5_IRQChannel           ((u8)0x17)  /* External Line[9:5] Interrupts */  

#define EXTI15_10_IRQChannel         ((u8)0x28)  /* External Line[15:10] Interrupts */


void NVIC_cfg(void);
void EXTI_cfg(void);

#endif 

