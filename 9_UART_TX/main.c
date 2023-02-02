#include <stdint.h>

#include "hwdef.h"
#include "uart.h"

void printString(char* str);

int main()
{
    // Initialize
    UART_Init();
    LED_Init();

    // Transmit
    printString("Enter the command:");

    for(;;);
}

void printString(char* str)
{
    while(*str)
    {
        UART_Transmit(*str++);
    }
}
