#include "key_led.h"

int main(void)
{
	
	LED_Configuration();
	Key_Configuration();
	
	while (1)
	{
		if(Key_Scan(GPIOA, GPIO_Pin_0) == Key_On)
		{
			LED_Flashing();
			LED_Flashing();
			LED_Flashing();
					
			LED_Breath();	
		}
	}
}

