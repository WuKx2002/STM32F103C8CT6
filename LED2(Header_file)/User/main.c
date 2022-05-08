#include "main.h"

void Delay(unsigned long nCount);

int main(void)
{
	RCC->APB2ENR |= (1<<2);
	
	GPIOA->CRL &= 0xFFF0000F;
	GPIOA->CRL |= 0x00033330;
	
	GPIOA->ODR &= ~((1<<1)|(1<<2)|(1<<3)|(1<<4));
	
	while(1)
	{
		GPIOA->ODR |= (1<<1)|(1<<2)|(1<<3)|(1<<4);
		Delay(0xFFFFFF);
		GPIOA->ODR &= ~((1<<1)|(1<<2)|(1<<3)|(1<<4));
		Delay(0xFFFFFF);
	}
}

void Delay(unsigned long nCount)
{
	while(nCount--);
}
