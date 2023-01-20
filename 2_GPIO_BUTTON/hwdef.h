#ifndef HWDEF_H_
#define HWDEF_H_

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

#endif