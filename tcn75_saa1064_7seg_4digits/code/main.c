//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tcn75/tcn75_c.h"
#include "./assets/saa1064/saa1064_c.h"
//------------------------------------------------------------------------------
tcn75_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	saa1064_init();
	tcn75_init(10, -3, RES_09_BIT, &sensor);	// Thermostat: High, Low, Resolution, and sensor object
	
	while(1)
	{ 	
		tcn75_setSensor(&sensor);
		
		saa1064_print("%5.1f", sensor.temp);
	}
}
//------------------------------------------------------------------------------
