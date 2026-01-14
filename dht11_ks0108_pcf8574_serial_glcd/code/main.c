//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/dht11/dht11_c.h"
#include "./assets/ks0108/ks0108_c.h"
//------------------------------------------------------------------------------
dht11_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();				 // Set Clock to 16Mhz	
	ks0108_init();

	ks0108_print(0, 7, font2, "*DHT11 Sensor*"); 
	ks0108_print(3, 0, font1, "Readings:");

	while(1)
	{ 
		if(dht11_getSensorData(&sensor))
		{	
			ks0108_print(5, 0, font1, "Humd:%4u%c", sensor.humidity, '%');		
			ks0108_print(6, 0, font1, "Temp:%4u°C", sensor.temperature);
		}
	}
}
//------------------------------------------------------------------------------
