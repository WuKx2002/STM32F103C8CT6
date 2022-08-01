#include "main.h"
#include "gpio.h"
#include "stm32f1xx_hal_gpio.h"

uint8_t gLEDIdx = 0;
uint16_t Light_PIN;
void SystemClock_Config(void);

int main(void)
{
	HAL_Init();

	SystemClock_Config();

	/*Configure NVIC*/
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);
	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	MX_GPIO_Init();

	while (1)
	{
		switch(gLEDIdx)
		{
			case 0: Light_PIN = GPIO_PIN_4;
					break;
			case 1: Light_PIN = GPIO_PIN_1;
					break;
			case 2: Light_PIN = GPIO_PIN_2;
					break;
			case 3: Light_PIN = GPIO_PIN_3;
					break;
			default:
					break;
		}
		HAL_GPIO_TogglePin(GPIOA, Light_PIN);
		HAL_Delay(500);
	}
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) 
{
	gLEDIdx = (gLEDIdx + 1) % 4;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_PIN_RESET);
}

void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9 ;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_SYSCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_SYSCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

