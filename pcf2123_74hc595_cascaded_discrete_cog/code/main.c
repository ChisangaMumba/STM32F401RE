//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/pcf2123/pcf2123_c.h"
#include "./assets/sevenSeg/sevenSeg_c.h"
//------------------------------------------------------------------------------
uint8_t time[7];	// Sec,Min,Hour,WDay,MDay,Month,Year
time_t tm;
uint8_t isColonOn = 0;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();					// Set Clock to 16Mhz	
	sevenSeg_init();
	pcf2123_init(time);	// Initialize pcf2123 RTC with initial time
	
	while(1)
	{ 
		pcf2123_getDateTime(&tm, time);	
		sevenSeg_print("%02d%02d%c", tm.hour, tm.minute, (isColonOn) ? '.' : '\0');	// Format time as HH:MM or HH MM alternatingly
		
		isColonOn = 1 - isColonOn; // toggle state;
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------
