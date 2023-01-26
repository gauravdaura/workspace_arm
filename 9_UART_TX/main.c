#include "hwdef.h"
#include "uart.h"

int main()
{
    // Initialize
    UART_Init();

    // Transmit
    while (1)
    {
        UART_Transmit('H');
        UART_Transmit('E');
        UART_Transmit('L');
        UART_Transmit('L');
        UART_Transmit('O');
        UART_Transmit('\n');
    }
}
