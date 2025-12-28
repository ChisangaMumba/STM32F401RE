//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds3234/ds3234_c.h"
#include "./assets/sevenSeg/sevenSeg_c.h"
//------------------------------------------------------------------------------
uint8_t time[8];	// Sec,Min,Hour,WDay,MDay,Month,Year
time_t tm; 
uint8_t isColonOn = 0;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	sevenSeg_init();
	ds3234_init(time);  //Initialize DS3234 RTC with initial time
	
	while(1)
	{ 		
		ds3234_getDateTime(&tm, time);
		sevenSeg_print("%02d%02d%c", tm.hour, tm.minute, (isColonOn) ? '.' : '\0'); // Toggle format between HH:MM and HH MM
		
		isColonOn = 1 - isColonOn; // toggle state;
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------
