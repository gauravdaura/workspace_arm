#include <stdio.h>
#include <stdint.h>
#include "hwdef.h"
#include "contact.h"

void Initialize(void);

CONTACT g_SW1;

int main(void)
{
    Initialize();
    
    // enable clock for button
    HWREG(SYSCTL_RCGCGPIO_R) = 0x20;
    // configure dir reg portf pin 1 as output and pin 4 as input
    HWREG(GPIO_PORTF_BASE + GPIO_O_DIR) |= LED_ON1;
    HWREG(GPIO_PORTF_BASE + GPIO_O_DIR) &= ~(PUSH_BUTTON);
    // configure pur register for portf pin 4 (pur reg needs lock reg and commit reg configured)
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_O_LOCKKEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= PUSH_BUTTON;
    HWREG(GPIO_PORTF_BASE + GPIO_O_PUR) |= PUSH_BUTTON;
    // configure dir reg for portf pin 1 and pin 4
    HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |= (1 << 4) | (1 << 1);
    // set data reg
    while (1)
    {
        if (CONTACT_Sample(&g_SW1))
        {
            if (g_SW1.bEventState == 0)
            {
                HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON1 << 2)) ^= LED_ON1;
            }
        }
    }
}

void Initialize(void)
{
    CONTACT_Init(&g_SW1, 100);
}