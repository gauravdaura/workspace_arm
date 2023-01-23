#include "systick.h"
#include "hwdef.h"
#include "global.h"

void SysTick_Init(void)
{ 
    NVIC_ST_RELOAD_R |= 160000 - 1;     // 100 ms 
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R |= 7;
}

void SysTick_IntHandler(void)
{
    // Flag a system tick event
    g_uiSysFlags |= ( 1 << SYSFLAGS_SYSTICK );
}
