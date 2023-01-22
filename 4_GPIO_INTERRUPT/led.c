#include "led.h"
#include "hwdef.h"

void LED_Init(void)
{
    // enable clock for button
    HWREG(SYSCTL_RCGCGPIO) |= 0x20;
    // configure direction register port-f pin
    HWREG(GPIO_PORTF_BASE + GPIO_O_DIR) |= LED_1;
    // configure digital enable register for port-f pin 1
    HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |= LED_1;
}
