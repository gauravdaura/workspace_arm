#include <stdio.h>
#include <stdint.h>

#define HWREG(x)            (*(( volatile unsigned long *) (x)))

#define SYSCTL_RCGCGPIO_R   0x400FE608
#define GPIO_PORTF_BASE     0x40025000
#define GPIO_O_DATA         0x00000000
#define GPIO_O_DIR          0x00000400
#define GPIO_O_DEN          0x0000051C
#define GPIO_O_PUR          0x00000510
#define GPIO_O_LOCK         0x00000520
#define GPIO_O_CR           0x00000524

#define GPIO_O_LOCKKEY      0x4C4F434B 
#define LED_ON1             0x02
#define PUSH_BUTTON         0x10

int main(void)
{
    uint32_t state = 0;
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
        if (!HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (PUSH_BUTTON << 2)))
        {
            HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON1 << 2)) ^= LED_ON1;
        }
    }
}
