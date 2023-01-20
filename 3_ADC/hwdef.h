#ifndef HWDEF_H_
#define HWDEF_H_

#define HWREG(x)            (*(( volatile unsigned long *) (x)))

#define SYSCTL_RCGCGPIO 0x400FE608 // hw_sysctl
#define SYSCTL_RCGCUART 0x400FE618 // hw_sysctl
#define SYSCTL_RCGCADC  0x400FE638 // hw_sysctl

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
#define GPIO_O_PUR      0x00000510 // hw_gpio
#define GPIO_O_PDR      0x00000514 // hw_gpio

#define UART0_BASE      0x4000C000 // hw_memmap

#define UART_O_DR       0x00000000 // hw_uart
#define UART_O_FR       0x00000018 // hw_uart
#define UART_O_IBRD     0x00000024 // hw_uart
#define UART_O_FBRD     0x00000028 // hw_uart
#define UART_O_CTL      0x00000030 // hw_uart
#define UART_O_IM       0x00000038 // hw_uart
#define UART_O_RIS      0x0000003C // hw_uart
#define UART_O_MIS      0x00000040 // hw_uart
#define UART_O_ICR      0x00000044 // hw_uart
#define UART_O_LCRH     0x0000002C // hw_uart

#define ADC0_BASE       0x40038000 // hw_memmap

#define ADC_O_ACTSS     0x00000000 // hw_adc
#define ADC_O_IM        0x00000008 // hw_adc
#define ADC_O_ISC       0x0000000C // hw_adc
#define ADC_O_EMUX      0x00000014 // hw_adc
#define ADC_O_SSPRI     0x00000020 // hw_adc
#define ADC_O_PSSI      0x00000028 // hw_adc
#define ADC_O_SAC       0x00000030 // hw_adc
#define ADC_O_SSMUX0    0x00000040 // hw_adc
#define ADC_O_SSCTL0    0x00000044 // hw_adc
#define ADC_O_SSFIFO0   0x00000048 // hw_adc
#define ADC_O_SSFSTAT0  0x0000004C // hw_adc
#define ADC_O_RIS       0x00000004 // hw_adc

#define NVIC_EN0        0xE000E100 // hw_nvic
#define NVIC_DIS0       0xE000E180 // hw_nvic

#define GPIO_O_LOCKKEY      0x4C4F434B
#define LED_ON1             0x02

#endif	// HWDEF_H_
