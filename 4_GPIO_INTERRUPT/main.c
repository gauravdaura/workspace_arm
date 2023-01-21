
int main(void)
{
    // whenever the user presses either of the push buttons,
    // an interrupt will be generated and TM4C123 microcontroller
    // executes the interrupt handler function of PORTF.
    // PF0 and PF4 SW, Red LED.

    // Inside the PORTF interrupt handler function,
    // we will turn on the onboard green LED of TM4C123 Tiva C launchpad,
    // if SW1 is pressed and turns off the LED if SW2 is pressed.

	return 0;
}
