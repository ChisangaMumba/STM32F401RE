//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bme280/bme280_c.h"
#include "./assets/max6954/max6954_c.h"
//------------------------------------------------------------------------------
char str[40];
float humd, temp;
bme280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				// Set Clock to 16Mhz	
	max6954_init(1);	// Number of chips connected in parallel
	bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode

	while(1)
	{		 
		temp = bme280_getTemp(calib);
		humd = bme280_getHum(calib);
		
		sprintf(str, "%5.1f°C%6.1fP", temp, humd); 
		max6954_displayText(str);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------

