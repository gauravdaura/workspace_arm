#include "contact.h"
#include "hwdef.h"

bool CONTACT_Init(CONTACT* pContact, uint32_t uiWindow)
{
    pContact->bCurrentState = 0;
    pContact->bPreviousState = 0;

    pContact->uiCount = 0;
    pContact->uiWindow = uiWindow;

    pContact->bEventState = 0;
    pContact->bEvent = 0;

    pContact->bReserved = 0;
}

bool CONTACT_Sample(CONTACT* pContact)
{
    // Read current state
    pContact->bCurrentState = HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (PUSH_BUTTON << 2));

    // Update counter if the contact has stablised. If not, reset counter
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