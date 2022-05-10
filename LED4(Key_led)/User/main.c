#include "key_led.h"

int main(void)
{
	LED_Configuration();
	Key_Configuration();
	
	while (1)
	{
		if(Key_Scan(GPIOA, GPIO_Pin_0) == KEY_ON)
			GPIOA->ODR ^= GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4; 
	}
}

