#ifndef __KEY_LED_H__
#define __KEY_LED_H__

#include <stm32f10x.h>

#define Key_On 	0
#define Key_Off 1

void Delay(unsigned long nCount);
void LED_Configuration(void);
void Key_Configuration(void);
int Key_Scan(GPIO_TypeDef* GPIOx, unsigned int Pin);

#endif

