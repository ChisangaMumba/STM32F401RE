//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/htu21/htu21_c.h"
#include "./assets/max6955/max6955_c.h"
//------------------------------------------------------------------------------
char str[40];
uint16_t rawHumd, rawTemp;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();					// Set Clock to 16Mhz	
	max6955_init(1);		// Number of chips connected in parallel
	htu21_init(RES_3);	// Internal pull-up is enabled within the gpio configurations, hence no external resistor

	while(1)
	{		 
		rawHumd = htu21_readConv(HUMD_NO_HOLD_CMD);
		rawTemp = htu21_readConv(TEMP_NO_HOLD_CMD);
		
		sprintf(str, "%5.1fP%6.1f°C", htu21_calcHumd(rawHumd), htu21_calcTemp(rawTemp)); 
		max6955_displayText(str);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------

