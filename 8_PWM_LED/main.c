#include <stdint.h>
#include "hwdef.h"
#include "global.h"
#include "pwm.h"
#include "systick.h"

void Delay_ms(int n);

int main(void)
{
    uint32_t g_uiDutyCycle = 5000;

//	SysTick_Init();
	PWM_Init();

    while(1)
    {
        // update cmpA register
        g_uiDutyCycle = g_uiDutyCycle - 10;
        if (g_uiDutyCycle <= 0)
            g_uiDutyCycle = 5000;
        PWM1_3_CMPA_R = g_uiDutyCycle;

        Delay_ms(100);
    }

//	while(1)
//	{
//	    // check systick flag
//		if (g_uiSysFlags & (1 << SYSFLAGS_SYSTICK))
//		{
//		    // clear the flag
//		    g_uiSysFlags &= ~(1 << SYSFLAGS_SYSTICK);
//
//		    // update cmpA register
//			g_uiDutyCycle = g_uiDutyCycle - 10;
//			if (g_uiDutyCycle <= 0)
//			{
//				g_uiDutyCycle = 5000;
//			}
//			PWM1_3_CMPA_R = g_uiDutyCycle;
//		}
}

/* This function generates delay in ms */
/* calculations are based on 16MHz system clock frequency */

void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* execute NOP for 1ms */
}
