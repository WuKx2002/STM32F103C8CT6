#include "main.h"
#include "gpio.h"

uint8_t Key_Num = 0;
uint8_t Key_Scan(void);
uint8_t cnt = 5;

int main(void)
{
	HAL_Init();
	MX_GPIO_Init();

	while (1)
	{
		Key_Num = 0;
		if (Key_Scan() == 1)
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
		}
		if (Key_Scan() == 2)
		{
			while(cnt--)
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
				HAL_Delay(500);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
				HAL_Delay(500);
			}
		}
	}
}

uint8_t Key_Scan(void)
{
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)
	{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)
		{
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0);
			Key_Num = 1;
		}
	}
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 0)
	{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 0)
		{
			while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == 0);
			Key_Num = 2;
		}
	}
	return Key_Num;
}
