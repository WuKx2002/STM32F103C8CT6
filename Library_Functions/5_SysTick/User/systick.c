#include "stm32f10x.h"
#include "systick.h"

/*SysTick相关函数
	SysTick_CLKSourceConfig()          	Systick选择时钟源(FWLIB-misc.c文件中)
	SysTick_Config(uint32_t ticks)     	初始化Systick(CORE-core_cm3.h文件中)
	void SysTick_Handler(void);			SysTick中断服务函数
*/

uint32_t TimingDelay;

void SysTick_Init(void)
{
	//SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	while(SysTick_Config(72));
	SysTick->CTRL &= ~(1<<0);			//暂时关闭定时器，使用时开启
}


void SysTick_Delay_us(uint32_t n)
{
	TimingDelay = n;
	SysTick->CTRL |= (1<<0);
	while(TimingDelay--);
	SysTick->CTRL &= ~(1<<0);
}
