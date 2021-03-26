#ifndef __DELAY_H_
#define __DELAY_H_
#include "stm32f10x.h"
#ifndef __DELAY_C_
#define __DELAY_Ex_  extern
#else 
#define __DELAY_Ex_
#endif


void delay_ms(u16 nms);
void delay_us(u32 nus);

void DelayInit(void);

#endif
