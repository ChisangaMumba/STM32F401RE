//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/delay/delay_c.h"
#include "./assets/hc_sr04/hc_sr04_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
uint16_t distance = 0;
//------------------------------------------------------------------------------
int main(void)
{
	system_config();	// Set Clock to 16Mhz
	lcd_init();
	hcsr04_tim2_cc1Init(TRIG, ECHO);
	
	while (1)
	{
		distance = (int) hcsr04_getDistance(TRIG);
		
		lcd_bargraph(0, distance, 400);  							// row, input, input max (400cm here)
		lcd_print(1, 0, "Measure:%5ucm", distance);			// row, col, string, args
	}
}
//------------------------------------------------------------------------------
