#include "systick.h"
#include "hwdef.h"

void SysTick_Init(void)
{ 
    NVIC_ST_RELOAD_R |= 16000000 - 1; 
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R |= 0x05;
}
