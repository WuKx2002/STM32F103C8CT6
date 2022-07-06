#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include <stdio.h>

int main(void)
{  
	uint8_t KeyNum = 0 ;
	
    LED_Init();
	Key_Init();
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
			LED_Set(LED1, LED_ON);
		if (KeyNum == 2)
			LED_Turn(LED2);
	}
}

