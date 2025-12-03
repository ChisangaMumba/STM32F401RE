//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tcn75/tcn75_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
char str[15];
tcn75_t sensor;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	tcn75_init(32, 20, RES_10_BIT, &sensor);  // Thermostat: High, Low, Resolution, and sensor object

	while(1)
	{
		tcn75_setSensor(&sensor); 
		
		sprintf(str, "%7.2f°C", sensor.temp); 
		ht16k33_displayText(str);
	}
}
//------------------------------------------------------------------------------

