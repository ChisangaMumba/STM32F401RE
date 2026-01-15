//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/th02/th02_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();		// Set Clock to 16Mhz	
	lcd_init();
	th02_init();		// 
	
	while(1)
	{
		lcd_print(0, 0, "Humd:%7.2f%c", th02_getHumd(), '%');
		lcd_print(1, 0, "Temp:%7.2f°C", th02_getTemp());
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
