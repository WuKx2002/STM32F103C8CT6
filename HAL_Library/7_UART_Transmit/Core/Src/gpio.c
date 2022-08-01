/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
#include "stm32f1xx_hal_uart.h"
/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/


/** Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 */

UART_HandleTypeDef Huart1;

void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*USART1 Clock Enable*/
	__HAL_RCC_USART1_CLK_ENABLE();

	/*Configure GPIO pin : PA9 (USART1 Tx) */
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	/*Configure GPIO pin : PA0 (Show System Clock Error) */
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure USART1 */
	Huart1.Instance = USART1;
	Huart1.Init.Mode = UART_MODE_TX;
	Huart1.Init.BaudRate = 9600;
	Huart1.Init.StopBits = UART_STOPBITS_1;
	Huart1.Init.WordLength = UART_WORDLENGTH_8B;
	Huart1.Init.Parity = UART_PARITY_NONE;
	Huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&Huart1) != HAL_OK)
		Error_Handler();
}

