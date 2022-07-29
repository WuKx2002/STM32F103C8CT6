#include "stm32f10x.h"
#include "LED.h"

#define GPIO_Pin_1_to_4 (GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4)

void AllLED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//GPIO_TypeDef *GPIO_InitStruct; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1_to_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void AllLED_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1_to_4) == 0)
		GPIO_SetBits(GPIOA, GPIO_Pin_1_to_4);
	else
		GPIO_ResetBits(GPIOA, GPIO_Pin_1_to_4);
}

