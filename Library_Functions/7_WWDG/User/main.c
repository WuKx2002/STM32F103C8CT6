#include "stm32f10x.h"
#include "stm32f10x_wwdg.h"
#include "WWDG.h"
#include "LED.h"
#include "Delay.h"

int main(void)
{  
	AllLED_Init();
	
	AllLED_Turn();
	Delay_ms(500);
	AllLED_Turn();
	Delay_ms(500);
	
	WWDG_Init(0x7F, 0x5F, WWDG_Prescaler_8);
	while(1)
	{
	}
}

