//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "assets/ds1620/ds1620_c.h"
#include "./assets/lcd8/lcd8_c.h"
//------------------------------------------------------------------------------
int temp[3];
char str[20];
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	lcd_init();
	ds1620_init(10, -5); //Set thermostat high and low values
	
	temp[0] = ds1620_getTemp(READ_TH);
	temp[1] = ds1620_getTemp(READ_TL);
	
	sprintf(str, "H:%3i°C,L:%3i°C", temp[0], temp[1]);
	lcd_string(0, 0, str); 
	
	while(1)
	{
	  temp[2] = ds1620_getTemp(READ_TEMP);
		
		sprintf(str, "Temp:%4i°C", temp[2]);
		lcd_string(1, 0, str);
		
		delay_ms(500);
	}
}
//------------------------------------------------------------------------------


