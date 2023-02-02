#include "led.h"
#include "hwdef.h"
#include "global.h"

void LED_Init(void)
{
    // enable clock for button
    SYSCTL_RCGCGPIO_R |= 0x20;
    // configure direction register port-f pin
    GPIO_PORTF_DIR_R |= LED_BLUE;
    // configure digital enable register for port-f pin 1
    GPIO_PORTF_DEN_R |= LED_BLUE;
}

void LED_Control(bool command)
{
    if (command)
        GPIO_PORTF_DATA_R |=   LED_BLUE;
    else
        GPIO_PORTF_DATA_R &= ~(LED_BLUE);
}
