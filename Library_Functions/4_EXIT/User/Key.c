#include "stm32f10x.h"
#include "Key.h"
#include "Delay.h"

#define KEY_OFF 0
#define KEY1_ON 1
#define KEY2_ON 2

void AllKey_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//GPIO_TypeDef *GPIO_InitStruct; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t Key_Scan(void)
{
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0)
		{
			while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
			return KEY1_ON;
		}
	}
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
	{
		Delay_ms(20);
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0)
		{
			while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5) == 0);
			return KEY2_ON;
		}
	}
	return KEY_OFF;
}