//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/dht11/dht11_c.h"
#include "./assets/sevenSeg/sevenSeg_c.h"
//------------------------------------------------------------------------------
dht11_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	sevenSeg_init();
		
	while(1)
	{
		if(dht11_getSensorData(&sensor))
		{
			sevenSeg_print("%2u", sensor.temperature);
		}
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------
