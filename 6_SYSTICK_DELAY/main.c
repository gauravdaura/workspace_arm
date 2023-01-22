#include "hwdef.h"
#include "led.h"
#include "systick.h"
#include "global.h"

int main(void)
{
	LED_Init();
	SysTick_Init();

	while(1)
	{	
		if (NVIC_ST_CTRL_R & (1 << 16))
		{

			GPIO_PORTF_DATA_R ^= LED_1;
		}
	}
}
