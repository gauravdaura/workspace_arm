#include <stdint.h>
#include "hwdef.h"
#include "global.h"
#include "pwm.h"
#include "systick.h"

int main(void)
{
    int32_t iDutyCycle = 1024;

	SysTick_Init();
	PWM_Init();

	while(1)
	{
	    // check SYSTICK flag
		if (g_uiSysFlags & (1 << SYSFLAGS_SYSTICK))
		{
		    // clear the flag
		    g_uiSysFlags &= ~(1 << SYSFLAGS_SYSTICK);

		    // update cmpA register
			iDutyCycle = iDutyCycle - 10;
			if (iDutyCycle <= 0)
			{
				iDutyCycle = 1024;
			}
			PWM1_3_CMPA_R = iDutyCycle;
		}
	}
}
