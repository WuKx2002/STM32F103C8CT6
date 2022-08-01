/* Includes ---------------------------------------------------------------------*/

#include "gpio.h"

/* Private define ---------------------------------------------------------------*/

#define VUART_GPIO_PORT GPIOA
#define VUART_GPIO_PIN 	GPIO_PIN_1

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Tx Line output high level by default*/
	HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);

	/*Configure GPIO pin : PA1 */
	GPIO_InitStruct.Pin = VUART_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(VUART_GPIO_PORT, &GPIO_InitStruct);
}
