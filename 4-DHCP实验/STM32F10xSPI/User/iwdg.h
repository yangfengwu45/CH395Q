#ifndef IWDG_H_
#define IWDG_H_

#include <stm32f10x.h>

#ifdef  IWDG_C_
#define IWDG_C_
#else
#define IWDG_C_ extern
#endif

void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);


#endif
