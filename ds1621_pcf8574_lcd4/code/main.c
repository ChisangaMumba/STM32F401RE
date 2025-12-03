//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds1621/ds1621_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[20];
float temp[3];
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 		// Set Clock to 16Mhz	
	lcd_init();
	ds1621_init(8, -5);	// Thermostat: High, Low
	
	temp[1] = ds1621_getTemp(TH_REG);	// TH
	temp[0] = ds1621_getTemp(TL_REG);	// TL
	
	sprintf(str, "H:%3i°C, L:%3i°C", (int)temp[1], (int)temp[0]);
	lcd_string(0, 0, str);
	
	while(1)
	{ 	
		temp[2] = ds1621_getTemp(TEMP_REG);
		
		sprintf(str, "Temp: %5.1f°C", temp[2]);
		lcd_string(1, 0, str);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------
