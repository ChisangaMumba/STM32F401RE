//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/adc/adc_c.h"
#include "./assets/bargraph/bargraph_c.h"
#include "./assets/max7219/max7219_c.h"
#define	 adcPin  PA6
//------------------------------------------------------------------------------
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{	  
	clock_init();				// Set Clock to 16Mhz	
	max7219_init(1);		// Number of chips connected in daisy chain
	bargraph_init();
	adc_init(adc1, adcPin);

	while(1)
	{
		temp = adc_getVoltage(adc1, adcPin);
		
		max7219_print( "%7.1f°C", temp);
		bargraph_write((int) temp);
	}
}
//------------------------------------------------------------------------------
