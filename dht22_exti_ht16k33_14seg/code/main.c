//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/exti/extInterrupt_c.h"
#include "./assets/bargraph/bargraph_c.h"
#include "./assets/dht22/dht22_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
dht22_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();	// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	bargraph_init();
	extInt_init(PA6, RISING_EDGE);
	
	while(1)
	{
		if(dht22_getSensorData(&sensor))
		{
			if(isTempMode == 0)
				ht16k33_print("%8.1f%c", sensor.humidity, '%');
			if(isTempMode == 1)
				ht16k33_print("%7.1f°C", sensor.temperature);
	
			bargraph_write((int)sensor.humidity);
		}
		else
				ht16k33_print("%8s", "Error");
		
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------
