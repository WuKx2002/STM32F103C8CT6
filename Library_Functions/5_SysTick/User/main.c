#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "systick.h"

int main(void)
{  
    AllLED_Init();
	SysTick_Init();
	
	AllLED_Turn();
	Delay_ms(1000);
	AllLED_Turn();
	
	while(1)
	{
		SysTick_Delay_us(10000000);
		AllLED_Turn();
	}
}
