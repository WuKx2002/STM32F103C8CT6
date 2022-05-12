#include <stm32f10x.h>

void Delay(unsigned long nCount);

int main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4); 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	while(1)
	{
		GPIO_WriteBit(GPIOA, (GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4), Bit_SET);
		Delay(0xFFFFF);
		GPIO_WriteBit(GPIOA, (GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4), Bit_RESET);
		Delay(0xFFFFF);
	}
}

void Delay(unsigned long nCount)
{
	while(nCount--);
}

