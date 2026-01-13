//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ads101x/ads101x_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[30];
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 		// Set Clock to 16Mhz	
	lcd_init();
	ads101x_init();
	
	lcd_print(0, 6, "ADS1015 sensor");
	lcd_print(1, 0, "Differential Mode:");
	
	while(1)
	{ 
		lcd_print(2, 0, "CH0_CH1:%7.2f°C", ads101x_getVoltage(DIFFERENTIAL_MODE, 0) * 100);
		lcd_print(3, 0, "CH2_CH3:%7.2f°C", ads101x_getVoltage(DIFFERENTIAL_MODE, 3) * 100);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
