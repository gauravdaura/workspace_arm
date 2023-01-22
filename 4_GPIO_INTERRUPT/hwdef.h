#ifndef HWDEF_H_
#define HWDEF_H_

#define HWREG(x)        (*(( volatile unsigned long *) (x)))

#define SYSCTL_RCGCGPIO 0x400FE608 // hw_sysctl

#define GPIO_PORTA_BASE 0x40004000 // hw_memmap
#define GPIO_PORTB_BASE 0x40005000 // hw_memmap
#define GPIO_PORTC_BASE 0x40006000 // hw_memmap
#define GPIO_PORTD_BASE 0x40007000 // hw_memmap
#define GPIO_PORTE_BASE 0x40024000 // hw_memmap
#define GPIO_PORTF_BASE 0x40025000 // hw_memmap

#define GPIO_O_DATA     0x00000000 // hw_gpio
#define GPIO_O_DIR      0x00000400 // hw_gpio
#define GPIO_O_AFSEL    0x00000420 // hw_gpio
#define GPIO_O_DEN      0x0000051C // hw_gpio
#define GPIO_O_AMSEL    0x00000528 // hw_gpio
#define GPIO_O_PCTL     0x0000052C // hw_gpio
#define GPIO_O_PDR      0x00000514 // hw_gpio
#define GPIO_O_PUR      0x00000510 // hw_gpio
#define GPIO_O_LOCK     0x00000520 // hw_gpio
#define GPIO_O_CR       0x00000524 // hw_gpio
#define GPIO_IM         0x00000410 // hw_gpio
#define GPIO_IS         0x00000404 // hw_gpio
#define GPIO_IBE        0x00000408 // hw_gpio
#define GPIO_IEV        0x0000040C // hw_gpio
#define GPIO_ICR        0x0000041C // hw_gpio
#define GPIO_MIS        0x00000418 // hw_gpio

#define NVIC_EN0        0xE000E100 // hw_nvic
#define NVIC_DIS0       0xE000E180 // hw_nvic
#define NVIC_PRI7       0xE000E41C // hw_nvic

#define GPIO_O_LOCKKEY  0x4C4F434B
#define LED_1           0x02
#define SW1             0x10
#define SW2             0x01

#endif	// HWDEF_H_
