#include "stm32f10x.h"
#include "WWDG.h"

uint8_t WWGF_CNT = 0x7F;

void WWDG_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel = WWDG_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
}

void WWDG_Init(uint8_t tr, uint8_t wr, uint8_t pr)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	WWGF_CNT &= tr;
//	WWDG_SetCounter(WWGF_CNT);
	WWDG_SetPrescaler(pr);
	WWDG_SetWindowValue(wr);
	WWDG_Enable(WWGF_CNT);
	
	WWDG_NVIC_Init();
	WWDG_ClearFlag();
	WWDG_EnableIT();
}
	
void WWDG_IRQHandler(void)
{
	WWDG_SetCounter(WWGF_CNT);
	WWDG_ClearFlag();
}

