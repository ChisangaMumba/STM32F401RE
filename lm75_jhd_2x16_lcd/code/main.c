//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/lm75/lm75_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[20];
lm75_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	lcd_init();
	lm75_init(10, -3, &sensor);	// Thermostat: High, Low, and sensor object

	sprintf(str, "H:%3i°C,L:%3i°C", (int)sensor.tempHigh, (int)sensor.tempLow);
	lcd_string(0, 0, str);
	
	while(1)
	{ 	
		lm75_setSensor(&sensor);
		
		sprintf(str, "Temp:%6.1f°C", sensor.temp);
		lcd_string(1, 0, str);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
