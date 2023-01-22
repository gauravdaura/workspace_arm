#include <stdio.h>
#include <stdint.h>
#include "hwdef.h"
#include "contact.h"
#include "led.h"

void Initialize(void);

CONTACT g_SW1;
CONTACT g_SW2;

int main(void)
{
    Initialize();

    while (1)
    {
        if (CONTACT_Sample(&g_SW1))
        {
            if (g_SW1.bEventState == 0)
            {
                LED_Toggle();
            }
        }
        if (CONTACT_Sample(&g_SW2))
        {
            if (g_SW2.bEventState == 0)
            {
                LED_Toggle();
            }
        }
    }
}

void Initialize(void)
{
    LED_Init();
    CONTACT_Init(&g_SW1, 100, 5, 4);
    CONTACT_Init(&g_SW2, 100, 5, 0);
}
