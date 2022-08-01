#include "main.h"
#include "gpio.h"

EXTI_HandleTypeDef hextiLine0;
void EXTI0Cbfn(void);

int main(void)
{
	HAL_Init(); 
	MX_GPIO_Init();

	EXTI_ConfigTypeDef pExtiConfig;
	pExtiConfig.Line = EXTI_LINE_0;
	pExtiConfig.Mode = EXTI_MODE_INTERRUPT;
	pExtiConfig.Trigger = EXTI_TRIGGER_RISING;
	pExtiConfig.GPIOSel = EXTI_GPIOA;
	__HAL_RCC_AFIO_CLK_ENABLE();
	HAL_EXTI_SetConfigLine(&hextiLine0, &pExtiConfig);

	HAL_EXTI_RegisterCallback(&hextiLine0, HAL_EXTI_COMMON_CB_ID, EXTI0Cbfn);

	/*Configure NVIC*/
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	while (1)
	{
	}
}

void EXTI0Cbfn(void)
{	
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
}

void EXTI0_IRQHandler(void)
{
	HAL_EXTI_IRQHandler(&hextiLine0);
}
