//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bargraph/bargraph_c.h"
#include "./assets/dht22/dht22_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
dht22_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();					// Set Clock to 16Mhz	
	max7219_init(1);		// Number of chips connected in daisy chain
	bargraph_init();
	
	while(1)
	{
		if(dht22_getSensorData(&sensor))
		{
			max7219_print("%7.1fRH", sensor.humidity);
			bargraph_write((int)sensor.humidity);
		}
		else
				max7219_print("Error");
	}
}
//------------------------------------------------------------------------------
