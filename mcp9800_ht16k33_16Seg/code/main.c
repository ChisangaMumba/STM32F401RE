//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/mcp9800/mcp9800_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
char str[20];
mcp9800_config_t tempConfig;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	mcp9800_init(20, 12, RES10_BIT, &tempConfig);  // Thermostat: High, Low, Resolution.

	while(1)
	{ 		
		sprintf(str, "%6.2f°C", mcp9800_getTemp()); 
		ht16k33_displayText(str);
		
		mcp9800_convDelay(tempConfig.res);   // Get delay based on resolution
	}
}
//------------------------------------------------------------------------------

