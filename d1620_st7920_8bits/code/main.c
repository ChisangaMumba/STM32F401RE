//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "assets/ds1620/ds1620_c.h"
#include "./assets/st7920/st7920_c.h"
//------------------------------------------------------------------------------
char str[30];
ds1620_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	st7920_init();
	ds1620_init(10, -5, &sensor); //Set thermostat high, low, and sensor object
	
	st7920_print(0, 1, "DS1620 Sensor"); 
	st7920_print(1, 0, "High:%4i°C", sensor.tempHigh); 
	st7920_print(2, 0, "Low:%5i°C", sensor.tempLow); 
	
	while(1)
	{
		ds1631_setSensor(&sensor);
	
		st7920_print(3, 0, "Temp:%4i°C", sensor.temp);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------


