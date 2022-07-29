#include "stm32f10x.h"
#include "IWDG.h"
#include "LED.h"
#include "Delay.h"
#include "Key.h"

int main(void)
{  
    IWDG_Init();
	AllLED_Init();
	Key_Init();
	
	Delay_ms(100);
	AllLED_Turn();
	
	while(1)
	{
		if (Key_GetNum() == 1)
			IWDG_Feed_Dog();
		Delay_ms(100);
	}
	
}

