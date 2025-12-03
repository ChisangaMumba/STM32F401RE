//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/adc/adc_c.h"
#include "./assets/tm1637/tm1637_c.h"
#define	 pin  PA3
//------------------------------------------------------------------------------
char str[10];
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 // Set Clock to 16Mhz	
	tm1637_init(8);    // init with brightness value. Valid values: 0 - 8.
	adc_init(adc1, pin);
	
	while(1)
	{		
		sprintf(str, "%5.1f°C", adc_getVoltage(adc1, pin));  
		tm1637_displayText(str);
		
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------

