#include "pwm.h"
#include "hwdef.h"
#include "global.h"

void PWM_Init(void)
{
    // 1. Enable the PWM clock
    SYSCTL_RCGCPWM_R    |=  0x02;
    // 2. Enable the clock to the appropriate GPIO module
    SYSCTL_RCGCGPIO_R   |=  PORTF;
    // 5. Configure the Run-Mode Clock Configuration (RCC) register in the System Control module
    // to use the PWM divide (USEPWMDIV) and set the divider (PWMDIV) to divide by 2 (000).
    SYSCTL_RCC_R        |=  (1 << 20);
    SYSCTL_RCC_R        |=  0x000E0000;
    // 3. In the GPIO module, enable the appropriate pins for their alternate function using the
    // GPIOAFSEL register. To determine which GPIOs to configure, see Table 23-4 on page 1344.
    GPIO_PORTF_AFSEL_R  |=  LED_BLUE;
    // 4. Configure the GPIOPCTL register to assign the PWM signals to the appropriate pins
    GPIO_PORTF_PCTL_R   &= ~(0x00000F00);
    GPIO_PORTF_PCTL_R   |=   0x00000500;
    GPIO_PORTF_DEN_R    |=   LED_BLUE;
    // 6. Configure the PWM generator for countdown mode with immediate updates to the parameters.
    // Write the PWM0CTL register with a value of 0x0000.0000.
    // Write the PWM0GENA register with a value of 0x0000.008C.
    // Write the PWM0GENB register with a value of 0x0000.080C.
    PWM1_3_CTL_R        &= ~(1 << 0);
    PWM1_3_CTL_R        &= ~(1 << 1);
    PWM1_3_GENA_R       |=  0x0000008c;
    // 7. Set load value for 50Hz 16MHz/65 = 250kHz and (250KHz/5000)
    // Use this value to set the PWM0LOAD register. In Count-Down mode, set the LOAD field in the
    // PWM0LOAD register to the requested period minus one.
    PWM1_3_LOAD_R       =   5000;
    // 8. Set the pulse width of the MnPWM0 pin to minimum initially.
    // Write the PWM0CMPA register
    PWM1_3_CMPA_R       =   4999;
    // 10. Start the timers in PWM generator 0.
    // Write the PWM0CTL register with a value of 0x0000.0001.
    PWM1_3_CTL_R        |=  0x01;
    // 11. Enable PWM outputs.
    // Write the PWMENABLE register with a value of 0x0000.0003.
    PWM1_ENABLE_R       |=  0x40;
}
