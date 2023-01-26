#include "hwdef.h"
#include "uart.h"
#include <stdint.h>

void UART_Transmit(char data)
{
    while ((UART5_FR_R & (1 << 5)) != 0);
    UART5_DR_R = data;
}

// char UART_Recieve(void)
// {
//     char data;
//     while ((UART5_FR_R & (1 << 4)) != 0);
//     data = (unsigned char)UART5_DR_R;

//     return data;
// }

void UART_Init(void)
{
    // To enable and initialize the UART, the following steps are necessary:
    // 1. Enable the UART module using the RCGCUART register
    SYSCTL_RCGCUART_R   |=  (1 << 5);

    // 2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register
    SYSCTL_RCGCGPIO_R   |=  (1 << 4);
    // 3. Set the GPIO AFSEL bits for the appropriate pins
    GPIO_PORTE_DEN_R    |=  0x30;
    GPIO_PORTE_AFSEL_R  |=  0x30;
    // 5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate pins
    GPIO_PORTE_PCTL_R    =  0x00110000;

    // With the BRD values in hand, the UART configuration is written to the module in the following order:
    // 1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
    UART5_CTL_R          = 0;
    // 2. Write the integer portion of the BRD to the UARTIBRD register.
    UART5_IBRD_R         = 104;
    // 3. Write the fractional portion of the BRD to the UARTFBRD register.
    UART5_FBRD_R         = 11;
    // 4. Write the desired serial parameters to the UARTLCRH register 
    UART5_LCRH_R         = (0x03 << 5);
    // 5. Configure the UART clock source by writing to the UARTCC register.
    // UART5_CC_R           = 0;
    // 6. Clear the flags register
    UART5_FR_R           = 0;
    // 7. Enable the UART by setting the UARTEN bit in the UARTCTL register
    UART5_CTL_R          = ((1 << 9) | (1 << 8) | (1 << 0));
}
