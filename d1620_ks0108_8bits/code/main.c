//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "assets/ds1620/ds1620_c.h"
#include "./assets/ks0108/ks0108_c.h"
//------------------------------------------------------------------------------
char str[30];
ds1620_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	ks0108_init();
	ds1620_init(10, -5, &sensor); //Set thermostat high, low, and sensor object
	
	ks0108_print(0, 12, font2, "DS1620 Sensor"); 
	
	ks0108_print(2, 0, font1, "Thermostat:"); 
	ks0108_print(3, 0, font1, "High:%4i°C", sensor.tempHigh); 
	ks0108_print(4, 0, font1, "Low:%5i°C", sensor.tempLow); 
	
	while(1)
	{
		ds1631_setSensor(&sensor);
		ks0108_print(6, 0, font1, "Temp:%4i°C", sensor.temp);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------


