//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/max31820/max31820_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[30];
max31820_t sensor; 
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 		// Set Clock to 16Mhz	
	lcd_init();
	max31820_init(32, 24, RES_09_BIT, &sensor);		// Thermostat: High, Low. Resolution. Sensor object
	
	lcd_print(0, 6, "Max31820");
	lcd_print(1, 0, "Thermostat:");
	lcd_print(2, 0, "HI:%3i°C, LO:%3i°C", sensor.tempHigh, sensor.tempLow);
	
	while(1)
	{ 
		lcd_print(3, 0, "Temp:%8.1f°C", max31820_readTemp());
		max31820_convDelay(sensor.resIndex);
	}
}
//------------------------------------------------------------------------------
