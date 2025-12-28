//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bargraph/bargraph_c.h"
#include "./assets/hc_sr04/hc_sr04_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
float distance;
//------------------------------------------------------------------------------
int main(void)
{	  
	system_config();		// Set Clock to 16Mhz	
	max7219_init(1);		// Number of chips connected in daisy chain
	bargraph_init();
	hcsr04_tim2_cc1Init(TRIG, ECHO);
	
	while(1)
	{		
		distance = hcsr04_getDistance(TRIG);
		
		if((distance != -1.0f) && (distance <= 400.0f))
		{
			uint16_t range = (int)distance;
			
			max7219_print("%4u", range);
			bargraph_write(range);
		}
		else
				max7219_print("E---");
		
		delay_ms(120);
	}
}
//------------------------------------------------------------------------------

