//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tcn75/tcn75_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
tcn75_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	lcd_init();
	tcn75_init(10, -3, RES_10_BIT, &sensor);	// Thermostat: High, Low, Resolution, and sensor object

	lcd_print(0, 0, "H:%3i°C,L:%3i°C", (int)sensor.tempHigh, (int)sensor.tempLow);
	
	while(1)
	{ 	
		tcn75_setSensor(&sensor);
		
		lcd_print(1, 0, "Temp:%7.2f°C", sensor.temp);
	}
}
//------------------------------------------------------------------------------
