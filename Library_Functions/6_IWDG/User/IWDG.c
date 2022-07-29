#include "IWDG.h"
#include "stm32f10x.h"

void IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_64);
	IWDG_SetReload(625);
	IWDG_ReloadCounter();
	IWDG_Enable();
}

void IWDG_Feed_Dog(void)
{
	IWDG_ReloadCounter();
}