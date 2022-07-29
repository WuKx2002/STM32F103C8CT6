#include "main.h"
#include "gpio.h"

void System_Clock(void);

int main(void)
{
	uint32_t n;

	HAL_Init();
	System_Clock();
	MX_GPIO_Init();

	while (1)
	{
		n = 1000000;
		do
		{
			__NOP();
		} while (n--);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
	}
}

void System_Clock(void)
{ 	
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK;
	RCC_ClkInitStruct.SYSCLKSource =  RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}
