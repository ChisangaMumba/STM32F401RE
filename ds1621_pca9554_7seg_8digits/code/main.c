//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds1621/ds1621_c.h"
#include "./assets/sevenSeg/sevenSeg_c.h"
//------------------------------------------------------------------------------
ds1621_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	sevenSeg_init();
	ds1621_init(20, 11, &sensor);	// Thermostat: High, Low, and sensor object
		
	while(1)
	{ 	
		ds1621_setSensor(&sensor);
		sevenSeg_print("%8.1f°C", sensor.temp);
	}
}
//------------------------------------------------------------------------------
