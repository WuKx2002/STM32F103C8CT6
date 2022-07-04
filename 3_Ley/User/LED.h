#ifndef __LED_H__
#define __LED_H__

#define LED1                GPIO_Pin_1
#define LED2                GPIO_Pin_2
#define LED3                GPIO_Pin_3
#define LED4                GPIO_Pin_4
#define LED_ON 				1
#define LED_OFF 			0

void LED_Init(void);
void LED_Set(uint16_t LEDx, uint8_t status);
void LED_Turn(uint16_t LEDx);
#endif
