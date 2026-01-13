//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds18b20/ds18b20_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[30];
ds18b20_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();		// Set Clock to 16Mhz	
	lcd_init();
	ds18b20_init();
	
	lcd_string(0, 4, "ds18b20");
	
	while(1)
	{ 		
		sprintf(str, "Temp:%5.1f°C", ds18b20_readTemp());
		lcd_string(1, 0, str);
	}
}
//------------------------------------------------------------------------------
