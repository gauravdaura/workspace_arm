#include <stdint.h>
#include "timer.h"
#include "hwdef.h"
#include "global.h"

void TIMER0_A_Init(void)
{
    // 0. Enable clock for Timer0
    SYSCTL_RCGCTIMER_R = 0x01;
    // 1. Ensure the timer is disabled (the TnEN bit in the GPTMCTL register is cleared)
    TIMER0_CTL_R = 0;
    // 2. Write the GPTM Configuration Register (GPTMCFG) with a value of 0x0000.0000.
    TIMER0_CFG_R |= 0x04;
    // 3. Configure the TnMR field in the GPTM Timer n Mode Register (GPTMTnMR):
    // a. Write a value of 0x1 for One-Shot mode.
    // b. Write a value of 0x2 for Periodic mode.
    TIMER0_TAMR_R |= 0x2;
    // 4. Optionally, set prescaler.
    TIMER0_TAPR_R |= 250 - 1;
    // 5. Load the start value into the GPTM Timer n Interval Load Register (GPTMTnILR).
    // 1 sec delay
    TIMER0_TAILR_R |= 64000 - 1;
    // 6. If interrupts are required, set the appropriate bits in the GPTM Interrupt Mask Register
    // (GPTMIMR).
    TIMER0_IMR_R = 0x01;
    // 7. Set the TnEN bit in the GPTMCTL register to enable the timer and start counting.
    TIMER0_CTL_R |= 0x01;
    // 8. Poll the GPTMRIS register or wait for the interrupt to be generated (if enabled). 
    TIMER0_ICR_R |= 0x01;
    
    // Enable Timer0_A in NVIC
    NVIC_EN0_R |= (1 << 19);
}

void Timer0_A_IntHandler(void)
{
    uint32_t uiIntStatus = TIMER0_MIS_R;

    if (uiIntStatus & (1 << 0))
    {
        // Clear the interrupt
        TIMER0_ICR_R |= 0x01;

        // set the Timer0_A flag
        g_uiSYSFLAGS = (1 << SYSFLAGS_TIMER0_A);
    }
}
