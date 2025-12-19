//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bmp280/bmp280_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
bmp280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	max7219_init(1);		// Number of chips connected in daisy chain
	bmp280_init(&calib, osrs_t_x1, osrs_p_x1, normal_mode); // Initialize BMP280 with 1x oversampling for both temperature and pressure in normal mode

	while(1)
	{		
		//max7219_print("%9.2f", 2516.79);	// Right justifies "   516.79"
		//max7219_print("%8d", 287);				// Right justifies "     287"
		//max7219_print("%8i", -34);					// Right justifies "     -34"
		//max7219_print("%7d%c", 157293, 'P');	// Right justifies " 157293P"
		//max7219_print("%8s", "HELP");			// Right justifies "    HELP"
		//max7219_print("%s", "HELP");	// "HELP    "			
		//max7219_print("HELP");		// "HELP    "	
		//max7219_print("%02d.%02d.20%02d", 3, 9, 25);  // 03.09.2025
		max7219_print("%9.2f", bmp280_getTemp(calib));
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------

