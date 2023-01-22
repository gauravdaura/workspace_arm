#include <stdint.h>
#include "global.h"
#include "hwdef.h"
#include "led.h"
#include "timer.h"

int main (void)
{
  LED_Init();
  TIMER0_A_Init();

  while (1)
  {
    // Timer0_A timeout occurred
    if (g_uiSYSFLAGS & (1 << 0))
    {
      // clear the System Flag
      g_uiSYSFLAGS &= ~(1 << SYSFLAGS_TIMER0_A);
      
      // Toggle Red LED
      GPIO_PORTF_DATA_R ^= LED_1;
    }
  }
}
