#include "hwdef.h"
#include "uart.h"
#include "led.h"
#include "global.h"
#include <stdint.h>

void UART_Transmit(char data)
{
    while ((UART0_FR_R & (1 << 5)) != 0);
    UART0_DR_R = data;
}

 void UART_IntHandler(void)
 {
    uint32_t uiIntStatus = UART0_MIS_R;
    uint8_t uidata;

    // Check Receive Interrupt
    if (uiIntStatus & (1 << 4))
    {
        // Clear the interrupt
        UART0_ICR_R     &= ~(1 << 4);

        // Read Data
        uidata = (unsigned char)UART0_DR_R;

        // Control Input
        if (uidata == 'A')
        {
            LED_Control(1);
        }
        else
        {
            LED_Control(0);
        }
    }

    UART_Transmit(uidata);
}


void UART_Init(void)
{
    // To enable and initialize the UART, the following steps are necessary:
    // 1. Enable the UART module using the RCGCUART register
    SYSCTL_RCGCUART_R   |=  0x01;
    // 2. Enable the clock to the appropriate GPIO module via the RCGCGPIO register
    SYSCTL_RCGCGPIO_R   |=  0x01;

    // 3. Set the GPIO AFSEL bits for the appropriate pins
    GPIO_PORTA_DEN_R    |=  0x03;
    GPIO_PORTA_AFSEL_R  |=  0x03;
    // 5. Configure the PMCn fields in the GPIOPCTL register to assign the UART signals to the appropriate pins
    GPIO_PORTA_PCTL_R    =  0x11;

    // With the BRD values in hand, the UART configuration is written to the module in the following order:
    // 1. Disable the UART by clearing the UARTEN bit in the UARTCTL register.
    UART0_CTL_R          = 0;
    // 2. Write the integer portion of the BRD to the UARTIBRD register.
    UART0_IBRD_R         = 8;
    // 3. Write the fractional portion of the BRD to the UARTFBRD register.
    UART0_FBRD_R         = 44;
    // 4. Write the desired serial parameters to the UARTLCRH register 
    UART0_LCRH_R         = (0x03 << 5);
    // 5. Configure the UART clock source by writing to the UARTCC register.
    UART0_CC_R           = 0;
    // 6. Clear the flags register
    UART0_FR_R           = 0;
    // 7. Enable the UART by setting the UARTEN bit in the UARTCTL register
    UART0_CTL_R          = (1 << 0) | (1 << 8) | (1 << 9);

    UART0_IM_R           |=  (1 << 4);
    NVIC_EN0_R           |=  (1 << 5);
}
