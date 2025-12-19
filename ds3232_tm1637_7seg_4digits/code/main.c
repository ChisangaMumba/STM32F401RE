//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds3232/ds3232_c.h"
#include "./assets/tm1637/tm1637_c.h"
//------------------------------------------------------------------------------
uint8_t time[8]; // Sec,Min,Hour,WDay,MDay,Month,Year
time_t tm;
uint8_t isColonOn = 0;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 // Set Clock to 16Mhz	
	tm1637_init(8);    // init with brightness value. Valid values: 0 - 8.
	ds3232_init(time);  //Initialize DS3232 RTC with initial time
	
	while(1)
	{
		ds3232_getDateTime(&tm, time);  
		tm1637_print("%02d%02d%c", tm.hour, tm.minute, (isColonOn) ? '.' : '\0');	// Format time as HH:MM or HH MM alternatingly
		
		isColonOn = 1 - isColonOn; // toggle state;
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------

