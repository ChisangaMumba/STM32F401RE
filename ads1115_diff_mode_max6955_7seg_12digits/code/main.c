//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ads111x/ads111x_c.h"
#include "./assets/max6955/max6955_c.h"
//------------------------------------------------------------------------------
float volts[2];
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();					// Set Clock to 16Mhz	
	max6955_init(1);		// Number of chips connected in parallel
	ads111x_init(); 

	while(1)
	{		 
		volts[0] = ads111x_getVoltage(DIFFERENTIAL_MODE, 0) * 100;
		volts[1] = ads111x_getVoltage(DIFFERENTIAL_MODE, 3) * 100;
		
		max6955_print("%5.1f°C%5.1f°C", volts[0], volts[1]);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------

