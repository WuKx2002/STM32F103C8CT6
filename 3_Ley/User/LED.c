#include "stm32f10x.h"
#include "LED.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
	//GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
}

void LED_Set(uint16_t LEDx, uint8_t status)
{
	if (status == LED_ON)
		GPIO_SetBits(GPIOA, LEDx);
	if (status == LED_OFF)
		GPIO_ResetBits(GPIOA, LEDx);
}

void LED_Turn(uint16_t LEDx)
{
	if (GPIO_ReadOutputDataBit(GPIOA, LEDx) == 0)
		GPIO_SetBits(GPIOA, LEDx);
	else
		GPIO_ResetBits(GPIOA, LEDx);
}


