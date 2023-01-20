#include <stdio.h>
#include "led.h"
#include "adc.h"
#include "hwdef.h"

void Initialize(void);

int main()
{
  uint32_t adc_value = 0;

  // system initialization
  Initialize();

  while(1)
  {
    // enable sampling                            ADCPSSI
    HWREG(ADC0_BASE + ADC_O_PSSI) |= (1 << 0);
    // wait for sample conversion to complete     ADC_O_RIS
    while((ADC0_BASE + ADC_O_RIS) == 0);
    // read adc conversion result                 ADC_O_SSFIFO0
    adc_value = HWREG(ADC0_BASE + ADC_O_SSFIFO0);
    // clear conversion flag
    HWREG(ADC0_BASE + ADC_O_ISC) &= ~(1 << 0);

    // control led
    if (adc_value >= 2048)
      HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON1 << 2)) |= LED_ON1;
    else if (adc_value < 2048)
      HWREG(GPIO_PORTF_BASE + GPIO_O_DATA + (LED_ON1 << 2)) &= ~LED_ON1;
  }
}

void Initialize(void)
{
  LED_Init();
  ADC_Init();
}
