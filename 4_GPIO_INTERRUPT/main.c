#include "led.h"
#include "hwdef.h"
#include "gpio.h"


int main(void)
{
    // Initialize system peripherals
    LED_Init();
    GPIO_Init();

    while (1)
    {
        // whenever the user presses either of the push buttons,
        // an interrupt will be generated and TM4C123 microcontroller
        // executes the interrupt handler function of PORTF.
        // PF0 and PF4 SW, Red LED.
    }
}
