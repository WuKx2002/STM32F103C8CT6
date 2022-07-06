#include "buzzer.h"
#include "stm32f10x.h"
#include "Delay.h"

void Buzzer_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Buzzer_ON(void)
{
	int cnt = 5;
	while (cnt--)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		Delay_ms(500);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		Delay_ms(500);
	}
}
