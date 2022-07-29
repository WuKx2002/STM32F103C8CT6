#ifndef __WWDG_H__
#define __WWDG_H__

void WWDG_NVIC_Init(void);
void WWDG_Init(uint8_t tr, uint8_t wr, uint8_t pr);
void WWDG_IRQHandler(void);
#endif 
