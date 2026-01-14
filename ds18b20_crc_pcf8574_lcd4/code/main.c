//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds18b20/ds18b20_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
ds18b20_t sensor; 
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();				 		// Set Clock to 16Mhz	
	lcd_init();
	ds18b20_init(32, 24, RES_09_BIT, &sensor);		// Thermostat: High, Low. Resolution. Sensor object
	
	lcd_print(0, 6, "ds18b20");
	lcd_print(1, 0, "Thermostats:");
	lcd_print(2, 0, "HI:%3i°C, LO:%3i°C", sensor.tempHigh, sensor.tempLow);
	
	while(1)
	{ 
		lcd_print(3, 0, "Temp:%8.1f°C", ds18b20_readTemp());
		ds18b20_convDelay(sensor.resIndex);
	}
}
//------------------------------------------------------------------------------
