#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f10x.h"

extern uint32_t TimingDelay;
void SysTick_Init(void);
void SysTick_Delay_us(uint32_t n);


#endif
