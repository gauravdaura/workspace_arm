#include "adc.h"
#include "hwdef.h"

void ADC_Init(void)
{
    // clock for ADC and GPIO
    HWREG(SYSCTL_RCGCADC) |= 0x01;
    HWREG(SYSCTL_RCGCGPIO) |= 0x08;

    /* Setup port-d of potentiometer */
    HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) |= (1 << 3);
    HWREG(GPIO_PORTD_BASE + GPIO_O_DEN)   &= ~(1 << 3);
    HWREG(GPIO_PORTD_BASE + GPIO_O_AMSEL) |= (1 << 3);

    /* Setup SS0 */
    // config SS priority                               ADCSSPRI
    HWREG(ADC0_BASE + ADC_O_SSPRI) &= 0x00003330;

    // disable SS0 before setup                         ADCACTSS
    HWREG(ADC0_BASE + ADC_O_ACTSS) &= ~(1 << 0);

    // configure trigger event                          ADCEMUX
    HWREG(ADC0_BASE + ADC_O_EMUX) &= 0x000FFF0;

    // configure PD3(ANI4) input source for the SS0     ADCSSMUXn
    HWREG(ADC0_BASE + ADC_O_SSMUX0) |= (1 << 3);

    // setup sample bits: 1st, 2nd, 3rd Sample: 0 0 E   0ADCSSCTLn
    HWREG(ADC0_BASE + ADC_O_SSCTL0) |= 0x0000000E;

    // MAYBE: enable hardware average                   ADC_O_SAC
//    HWREG(ADC0_BASE + ADC_O_SAC) = 6;

    // enable SS0 after setup                           ADCACTSS
    HWREG(ADC0_BASE + ADC_O_ACTSS) |= (1 << 0);

    // enable interrupts                                ADCIM, ADCISC
    // HWREG(ADC0_BASE + ADC_O_IM) |= (1 << 0);
    // HWREG(ADC0_BASE + ADC_O_ISC) |= (1 << 0);
    // HWREG(NVIC_EN0) = (1 << 14);
}
