//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bargraph/bargraph_c.h"
#include "./assets/hc_sr04/hc_sr04_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
uint16_t distance = 0;
//------------------------------------------------------------------------------
int main(void)
{	 	
	system_config();		// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	bargraph_init();
	hcsr04_tim2_cc1Init(TRIG, ECHO);

	while(1)
	{
		distance = (int) hcsr04_getDistance(TRIG); 
		
		ht16k33_print("%6dcm", distance);
		bargraph_write(distance);
		
		delay_ms(120);
	}
}
//------------------------------------------------------------------------------

