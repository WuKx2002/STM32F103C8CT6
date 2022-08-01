/* Includes --------------------------------------------------------------------*/

#include "main.h"

/* Private define ---------------------------------------------------------------*/

/**
	******************************************************************************
	Write A Delay Function
	It takes 1000MS to perform 800000 cycle through the following code test, 
	so 104.1/[(1000/8000000)*1000] = 833 cycles need to be executed.

	uint32_t Period;
	uint32_t StartTick;
	StartTick = HAL_GetTick();

	volatile uint32_t n = 8000000;
	do
	{
		__NOP();
	} while (n--);

	Period = HAL_GetTick() - StartTick;

	So we write such a delay function:

	void VUART_DelayOneSymbol(void)
	{
		uint32_t n = 833;
		do
		{
			__NOP();
		} while (n--);
	}

	In the actual program, we present this delay function in the form of #define;
	******************************************************************************
*/
#define VUART_GPIO_PORT 			GPIOA
#define VUART_GPIO_PIN 				GPIO_PIN_9

#define VUART_DELAY_ONE_SYMBOL()	n = 833; do{ __NOP(); } while (n--);

#define VUART_DATABITS_8 			((uint32_t)0x00)
#define VUART_DATABITS_9 			((uint32_t)0x01)

#define VUART_STOPBITS_1 			((uint32_t)0x00)
#define VUART_STOPBITS_2 			((uint32_t)0x01)

#define VUART_NOPARITY				((uint32_t)0x00)
#define VUART_ODDARITY				((uint32_t)0x01)
#define VUART_EVENARITY				((uint32_t)0x02)

/* Private typedef -----------------------------------------------------------*/

typedef struct
{
	uint32_t DataBits;
	uint32_t Parity;
	uint32_t StopBits;
	uint32_t Baudrate;
}VUART_InitTypeDef;

typedef struct
{
	VUART_InitTypeDef Init;
}VUART_HandleTypeDef;

/* Private variables ------------------------------------------------------------*/

uint32_t n;
VUART_HandleTypeDef Hvuart;

/* Private function prototypes --------------------------------------------------*/

void SystemClock_Config(void);
void VUART_Init(VUART_HandleTypeDef *Hvuart);
void VUART_Transmit(VUART_HandleTypeDef *Hvuart, uint16_t *pData, uint32_t Len);
void VUART_SendPrame(VUART_HandleTypeDef *Hvuart, uint16_t Data);

/* Private user code ------------------------------------------------------------*/

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	uint16_t pData[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
	
	HAL_Init();

	SystemClock_Config();

	Hvuart.Init.Baudrate = 9600;
	Hvuart.Init.DataBits = VUART_DATABITS_8;
	Hvuart.Init.StopBits = VUART_STOPBITS_1;
	Hvuart.Init.Parity = VUART_NOPARITY;

	VUART_Init(&Hvuart);
	while (1)
	{
		VUART_Transmit(&Hvuart, pData, 11);
		HAL_Delay(500);
	}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
	RCC_OscInitTypeDef RCC_OscInitStruct; 
	RCC_ClkInitTypeDef RCC_ClkInitStruct; 

	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);   

	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}


void VUART_Init(VUART_HandleTypeDef *Hvuart)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	UNUSED(Hvuart);

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Tx Line output high level by default*/
	HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);

	/*Configure GPIO pin : VUART_GPIO_PIN */
	GPIO_InitStruct.Pin = VUART_GPIO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(VUART_GPIO_PORT, &GPIO_InitStruct);
}

void VUART_SendPrame(VUART_HandleTypeDef *Hvuart, uint16_t Data)
{
	uint32_t i;
	uint32_t counter = 0;

	HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_RESET);
	VUART_DELAY_ONE_SYMBOL(); 

	for (i = 0; i < 7; i++)
	{
		if ((Data & (0x01 << i)) != 0)
		{
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);
			counter++;
		}
		else
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_RESET);
	}
	VUART_DELAY_ONE_SYMBOL(); 

	if(Hvuart->Init.DataBits == VUART_DATABITS_8 && Hvuart->Init.Parity != VUART_NOPARITY)
	{

	}
	else
	{
		if ((Data & (0x01 << 7)) != 0)
		{
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);
			counter++;
		}
		else
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_RESET);
		VUART_DELAY_ONE_SYMBOL(); 
	}

	if(Hvuart->Init.DataBits == VUART_DATABITS_9 && Hvuart->Init.Parity == VUART_NOPARITY)
	{
		
	}
	else
	{
		if ((Data & (0x01 << 8)) != 0)
		{
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);
			counter++;
		}
		else
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_RESET);
		VUART_DELAY_ONE_SYMBOL(); 
	}

	if(Hvuart->Init.Parity == VUART_ODDARITY)
	{
		if (counter % 2 == 0)
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_RESET);
		VUART_DELAY_ONE_SYMBOL(); 
	}

	if(Hvuart->Init.Parity == VUART_EVENARITY)
	{
		if (counter % 2 == 1)
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_RESET);
		VUART_DELAY_ONE_SYMBOL(); 
	}
	
	HAL_GPIO_WritePin(VUART_GPIO_PORT, VUART_GPIO_PIN, GPIO_PIN_SET);
	VUART_DELAY_ONE_SYMBOL(); 
	if(Hvuart->Init.StopBits == VUART_STOPBITS_2)
		VUART_DELAY_ONE_SYMBOL(); 
}

void VUART_Transmit(VUART_HandleTypeDef *Hvuart, uint16_t *pData, uint32_t Len)
{
	do
	{
		VUART_SendPrame(Hvuart, *pData++);
	} while (Len--);
}

