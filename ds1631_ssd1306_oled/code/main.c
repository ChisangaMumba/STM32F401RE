//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds1631/ds1631_c.h"
#include "./assets/ssd1306/ssd1306_c.h"
//------------------------------------------------------------------------------
char str[20];
ds1631_t tempConfig;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	ssd1306_init();
	ds1631_init(8, -5, RES12_BIT, &tempConfig);	// Thermostat: High, Low, Resolution, and temperature config
	
	ssd1306_print(0, 0, "Thermostat:");
	sprintf(str, "H:%3i°C, L:%3i°C", (int)tempConfig.tempHigh, (int)tempConfig.tempLow);
	ssd1306_print(1, 0, str);
	
	while(1)
	{ 			
		sprintf(str, "Value:%8.4f°C", ds1631_getTemp(TEMP_REG));
		ssd1306_print(3, 0, str);
		
		ds1631_convDelay(tempConfig.resolution);
	}
}
//------------------------------------------------------------------------------
