#include "contact.h"
#include "hwdef.h"

void CONTACT_Init(CONTACT *pContact, uint32_t uiWindow, uint8_t uiPort, uint8_t uiBit)
{
    pContact->uiPort = uiPort;
    pContact->uiBit = uiBit;

    // select port using switch(pContant->uiPort) and select address for the port
    switch (pContact->uiPort)
    {
    case 0: // Port A
        pContact->uiPortAddress = GPIO_PORTA_BASE;
        break;
    case 1: // Port B
        pContact->uiPortAddress = GPIO_PORTB_BASE;
        break;
    case 2: // Port C
        pContact->uiPortAddress = GPIO_PORTC_BASE;
        break;
    case 3: // Port D
        pContact->uiPortAddress = GPIO_PORTD_BASE;
        break;
    case 4: // Port E
        pContact->uiPortAddress = GPIO_PORTE_BASE;
        break;
    case 5: // Port F
        pContact->uiPortAddress = GPIO_PORTF_BASE;
        break;
    }

    // configure port and pins for the switch
    HWREG(SYSCTL_RCGCGPIO_R) = (1 << pContact->uiPort);
    // configure direction register for port-f pin
    HWREG(GPIO_PORTF_BASE + GPIO_O_DIR) &= ~(1 << pContact->uiBit);
    // configure PUR register for PORTF pin 4
    // (PUR register needs lock register and commit register configured)
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_O_LOCKKEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= pContact->uiBit;
    HWREG(GPIO_PORTF_BASE + GPIO_O_PUR) |= pContact->uiBit;
    // configure direction register for PORTF pin
    HWREG(GPIO_PORTF_BASE + GPIO_O_DEN) |= pContact->uiBit;

    // configure contact de-bounce states
    pContact->bCurrentState = 0;
    pContact->bPreviousState = 0;

    pContact->uiCount = 0;
    pContact->uiWindow = uiWindow;

    pContact->bEventState = 0;
    pContact->bEvent = 0;
    pContact->bReserved = 0;
}

bool CONTACT_Sample(CONTACT *pContact)
{
    // Read current state
    pContact->bCurrentState = !!HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (PUSH_BUTTON << 2));

    // Update counter if the contact has stabilized. If not, reset counter
    if (pContact->bCurrentState ^ pContact->bPreviousState)
    {
        // changed detected from previous state
        pContact->uiCount = pContact->uiWindow;
    }
    else
    {
        if (pContact->uiCount)
        {
            // no change detected from the previous state
            pContact->uiCount--;
        }
    }

    // Prepare next sample by setting previous state
    pContact->bPreviousState = pContact->bCurrentState;

    // Update Event and EventState for every count
    pContact->bEvent = pContact->uiCount == 1 ? 1 : 0;
    pContact->bEventState = pContact->uiCount == 1 ? pContact->bCurrentState : pContact->bEventState;

    return pContact->bEvent;
}
