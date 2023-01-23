#include "systick.h"
#include "hwdef.h"
#include "global.h"

void SysTick_Init(void)
{ 
    NVIC_ST_RELOAD_R |= 16000000 - 1; 
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R |= 7;
}

void SysTick_IntHandler(void)
{
    GPIO_PORTF_DATA_R ^= LED_1;
}
