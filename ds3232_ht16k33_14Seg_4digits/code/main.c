//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds3232/ds3232_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
uint8_t time[8]; // Sec,Min,Hour,WDay,MDay,Month,Year
time_t tm;
uint8_t isColonOn = 0;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	ds3232_init(time);  //Initialize DS3232 RTC with initial time

	while(1)
	{
		ds3232_getDateTime(&tm, time); 
		
		if(isColonOn)
			ht16k33_print("%02d%02d", tm.hour, tm.minute);
		else
			ht16k33_print("%02d.%02d", tm.hour, tm.minute);

		isColonOn = 1 - isColonOn; // toggle state;
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------

