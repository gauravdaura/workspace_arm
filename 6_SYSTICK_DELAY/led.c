#include "led.h"
#include "hwdef.h"
#include "global.h"

void LED_Init(void)
{
    // enable clock for button
    SYSCTL_RCGCGPIO_R |= 0x20;
    // configure direction register port-f pin
    GPIO_PORTF_DIR_R |= LED_1;
    // configure digital enable register for port-f pin 1
    GPIO_PORTF_DEN_R |= LED_1;
}

