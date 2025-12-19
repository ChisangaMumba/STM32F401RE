//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/mcp9800/mcp9800_c.h"
#include "./assets/max6955/max6955_c.h"
//------------------------------------------------------------------------------
char str[20];
mcp9800_config_t tempConfig;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();					// Set Clock to 16Mhz	
	max6955_init(1);		// Number of chips connected in parallel
	mcp9800_init(10, -5, RES11_BIT, &tempConfig);  // Thermostat: High, Low, Resolution.

	while(1)
	{		 
		sprintf(str, "%7.2f°C", mcp9800_getTemp()); 
		max6955_displayText(str);
		
		mcp9800_convDelay(tempConfig.res);   // Get delay based on resolution
	}
}
//------------------------------------------------------------------------------

