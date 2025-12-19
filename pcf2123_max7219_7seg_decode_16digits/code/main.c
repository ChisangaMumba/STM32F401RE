//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/pcf2123/pcf2123_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
char str[30];
uint8_t time[7];	// Sec,Min,Hour,WDay,MDay,Month,Year
time_t tm; 
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 		// Set Clock to 16Mhz	
	max7219_init(2);			// Number of chips connected in daisy chain
	pcf2123_init(time);  	// Initialize pcf2123 RTC with initial time

	while(1)
	{
		pcf2123_getDateTime(&tm, time);
  
		sprintf(str, "%02d.%02d.%02d  ", tm.hour, tm.minute, tm.second); // Format time as HH.MM.SS
		sprintf(str + strlen(str), "%02d.%02d.20%02d", tm.dayOfMonth, tm.month, tm.year); // Format date as DD.MM.YYYY
		
		max7219_displayText(str);
		
		delay_ms(20);
	}
}
//------------------------------------------------------------------------------

