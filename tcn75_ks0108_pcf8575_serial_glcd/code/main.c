//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tcn75/tcn75_c.h"
#include "./assets/ks0108/ks0108_c.h"
//------------------------------------------------------------------------------
char str[30];
tcn75_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	ks0108_init();
	tcn75_init(20, 11, RES_11_BIT, &sensor);	// Thermostat: High, Low, and sensor object
	
	ks0108_print(0, 14, font2, "Tcn75 Sensor"); 
	ks0108_print(2,  0, font1, "Thermostat:");
	ks0108_print(3,  0, font1, "HIGH:%7i°C", (int)sensor.tempHigh);
	ks0108_print(4,  0, font1, "LOW:%8i°C", (int)sensor.tempLow);
	
	while(1)
	{ 
		tcn75_setSensor(&sensor);
		
		ks0108_print(6, 0, font1, "Temp:%8.3f°C", sensor.temp);
	}
}
//------------------------------------------------------------------------------
