//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/dht11/dht11_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
dht11_t sensor;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	max7219_init(1);		// Number of chips connected in daisy chain

	while(1)
	{		
		if(dht11_getSensorData(&sensor))
		{
			max7219_print("%6i°C", sensor.temperature);
		}
		else
				max7219_print("%8s", "Err");
	
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------
