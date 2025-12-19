//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds3232/ds3232_c.h"
#include "./assets/ssd1306/ssd1306_c.h"
//------------------------------------------------------------------------------
uint8_t time[8];  // Sec,Min,Hour,WDay,MDay,Month,Year
time_t tm;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	ssd1306_init();
	ds3232_init(time);  //Initialize DS3232 RTC with initial time
	
	ssd1306_print(0, 45, "DS3232");
	
	while(1)
	{ 
		ds3232_getDateTime(&tm, time);

		ssd1306_print(1, 0, "Temp:%7.2f°C", ds3232_getTemp());
		ssd1306_print(2, 0, "Time:  %02d.%02d.%02d", tm.hour, tm.minute, tm.second);	// Format time as HH.MM.SS
		ssd1306_print(3, 0, "Date:  %02d.%02d.20%02d", tm.dayOfMonth, tm.month, tm.year);	// Format date as DD.MM.YYYY
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
