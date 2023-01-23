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
	    // wait for interrupt
	}
}
