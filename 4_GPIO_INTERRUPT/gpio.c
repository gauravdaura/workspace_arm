#include "stdint.h"
#include "gpio.h"
#include "hwdef.h"

void GPIO_IntHandler(void)
{
    // check interrupt status GPIOMIS
    if (HWREG(GPIO_PORTF_BASE + GPIO_MIS) & (1 << 4))
    {
        // clear interrupt to enable new interrupts GPIORIS
        HWREG(GPIO_PORTF_BASE + GPIO_ICR) |= (1 << 4);
        // enable led
        HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_1 << 2)) |= LED_1;
    }
    else if (HWREG(GPIO_PORTF_BASE + GPIO_MIS) & (1 << 0))
    {
        // clear interrupt to enable new interrupts GPIORIS
        HWREG(GPIO_PORTF_BASE + GPIO_ICR) |= (1 << 0);
        // enable led
        HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_1 << 2)) &= ~LED_1;
    }
    
}

void GPIO_Init(void)
{
    // enable clock
    HWREG(SYSCTL_RCGCGPIO) |= 0x20;
    // configure DEN
    HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |=  (SW1 | SW2);
    // configure direction
    HWREG(GPIO_PORTF_BASE + GPIO_O_DIR) &= ~(SW1 | SW2);
    // configure PULL-UP
    HWREG(GPIO_PORTF_BASE + GPIO_O_PUR) |=  (SW1 | SW2);

    // configure falling edge trigger detection
    HWREG(GPIO_PORTF_BASE + GPIO_IM)  &= ~(SW1 | SW2);
    HWREG(GPIO_PORTF_BASE + GPIO_IS)  &= ~(SW1 | SW2);
    HWREG(GPIO_PORTF_BASE + GPIO_IBE) &= ~(SW1 | SW2);
    HWREG(GPIO_PORTF_BASE + GPIO_IEV) &= ~(SW1 | SW2);
    HWREG(GPIO_PORTF_BASE + GPIO_ICR) |=  (SW1 | SW2);
    HWREG(GPIO_PORTF_BASE + GPIO_IM)  |=  (SW1 | SW2);

    // configure interrupts
    HWREG(NVIC_PRI7) = (3 << 20);
    HWREG(NVIC_EN0) |= (1 << 30);

    // unlock port
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_O_LOCKKEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR)  |= (SW1 | SW2);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
}