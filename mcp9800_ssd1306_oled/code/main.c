//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/mcp9800/mcp9800_c.h"
#include "./assets/ssd1306/ssd1306_c.h"
//------------------------------------------------------------------------------
char str[30];
mcp9800_config_t tempConfig;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	ssd1306_init();
	mcp9800_init(10, -5, RES11_BIT, &tempConfig);  // Thermostat: High, Low, Resolution.
	
	ssd1306_print(0, 28, "MCP9800 sensor");
	ssd1306_print(2,  0, "Thermometer:");

	sprintf(str, "Hi:%3i°C, Lo:%3i°C", tempConfig.tempHigh, tempConfig.tempLow);
	ssd1306_print(3, 0, str);
	
	while(1)
	{ 			
		sprintf(str, "Temp:%8.3f°C", mcp9800_getTemp());
		ssd1306_print(6, 0, str);
		
		mcp9800_convDelay(tempConfig.res);
	}
}
//------------------------------------------------------------------------------
