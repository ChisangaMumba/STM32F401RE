//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds1307/ds1307_c.h"
#include "./assets/max6955/max6955_c.h"
//------------------------------------------------------------------------------
char str[40];
uint8_t time[8]; // Sec,Min,Hour,WDay,MDay,Month,Year
time_t tm;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();					// Set Clock to 16Mhz	
	max6955_init(1);		// Number of chips connected in parallel
	ds1307_init(time);  // Initialize RTC with initial time

	while(1)
	{		 
		ds1307_getDateTime(&tm, time); 
		
		sprintf(str, "%02d.%02d.%02d", tm.hour, tm.minute, tm.second); // Format time as HH.MM.SS
		sprintf(str + strlen(str), "%02d.%02d.%02d", tm.dayOfMonth, tm.month, tm.year); // Format date as DD.MM.YYYY
		
		max6955_print(str);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------

