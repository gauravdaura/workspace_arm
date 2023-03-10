#include <stdio.h>

#define HWREG(x)            (*(( volatile unsigned long *) (x)))

#define SYSCTL_RCGCGPIO_R   0x400FE608
#define GPIO_PORTF_BASE     0x40025000
#define GPIO_O_DATA         0x00000000
#define GPIO_O_DIR          0x00000400
#define GPIO_O_DEN          0x0000051C

#define LED_ON1             0x02
#define LED_ON2             0x04
#define LED_ON3             0x08
#define DELAY               1000000

void delay(void);

int main(void)
{
  // enable port-f clock
  HWREG(SYSCTL_RCGCGPIO_R) |= 0x20;
  // configure pins as digital pin
  HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |= 0x0E;
  // configure pins direction
  HWREG(GPIO_PORTF_BASE + GPIO_O_DIR) |= 0x0E;
  // turn on led
  // HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (0x0E << 2)) |= 0x0E;
  while (1) 
  {  
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON3 << 2)) &= ~(LED_ON3);
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON2 << 2)) &= ~(LED_ON2);
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON1 << 2)) |= LED_ON1;
    delay();
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON3 << 2)) &= ~(LED_ON3);
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON1 << 2)) &= ~(LED_ON1);
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON2 << 2)) |= LED_ON2;
    delay();
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON2 << 2)) &= ~(LED_ON2);
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON1 << 2)) &= ~(LED_ON1);
    HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON3 << 2)) |= LED_ON3;
    delay();
  }
}

void delay(void)
{
  long unsigned int i;
  for(i = 0; i < DELAY; i++);
}
