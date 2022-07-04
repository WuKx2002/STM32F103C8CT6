#define RCC_APB2ENR 	(*(volatile unsigned long *)0x40021018)
#define GPIOA_CRL 		(*(volatile unsigned long *)0x40010800)
#define GPIOA_ODR 		(*(volatile unsigned long *)0x4001080C)

void Delay(unsigned long nCount);

int main(void)
{

	RCC_APB2ENR |= (1<<2);

	GPIOA_CRL &= 0xFFF0000F;
	GPIOA_CRL |= 0x00033330;
	
	GPIOA_ODR &= ~((1<<1)|(1<<2)|(1<<3)|(1<<4));
	
	while(1)
	{
		GPIOA_ODR |= (1<<1)|(1<<2)|(1<<3)|(1<<4);
		Delay(0xffffff);
		GPIOA_ODR &= ~((1<<1)|(1<<2)|(1<<3)|(1<<4));
		Delay(0xffffff);
	}

}

void Delay(unsigned long nCount)
{
	while(nCount--);
}
