//	Program Description
//	Use GPIO input to detect button 1.
//	Use exit external interrupt detection to detect button 2.
//	When button 1 is pressed, switch the mode of the 4 LEDs. 
//	When button 2 is pressed, open the buzzer.
	
#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "exti.h"

int main(void)
{  
	AllLED_Init();
	AllKey_Init();
	PA5_EXTI5_Init();
	
	while(1)
	{
		if (Key_Scan() == 1)
			AllLED_Turn();
	}
}

