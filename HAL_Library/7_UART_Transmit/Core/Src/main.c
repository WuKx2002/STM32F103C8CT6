/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "gpio.h"
#include "stm32f1xx_hal_uart.h"
#include <string.h>

/* Private function prototypes -----------------------------------------------*/


/* Private user code ---------------------------------------------------------*/
extern UART_HandleTypeDef Huart1;

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	const char *str = "Hello world";

	if (HAL_Init() != HAL_OK)
		Error_Handler();

	SystemClock_Config();

	MX_GPIO_Init();

	while (1)
	{
		HAL_UART_Transmit(&Huart1, (uint8_t *)str, strlen(str)*sizeof(char), HAL_MAX_DELAY);
		HAL_Delay(1000);
	}
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
		Error_Handler();

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
		Error_Handler();
}

void Error_Handler(void)
{
	/* Disable IRQ Interrupts*/
	__disable_irq();

	while (1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
		HAL_Delay(500);
	}
}


