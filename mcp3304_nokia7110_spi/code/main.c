//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/mcp330x/mcp330x_c.h"
#include "./assets/sed1565/sed1565_c.h"
//------------------------------------------------------------------------------
char str[40];
float volts[7];
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();			// Set Clock to 16Mhz	
	sed1565_init();
	mcp330x_init();
	
	/*
	sed1565_print(0, 27, "(MCP3304 adc)");
	sed1565_print(1, 50, "Lm35");
	*/
	sed1565_print(0, 12, "(MCP3304 adc)");
	sed1565_print(1, 40, "Lm35");
	
	while(1)
	{ 			
		// LM35 produces voltage equivalent to temperature
		// DIFFERENTIAL_MODE or SINGLE_MODE
		volts[0] = mcp330x_getVoltage(SINGLE_MODE, 0) * 100;	
		volts[1] = mcp330x_getVoltage(SINGLE_MODE, 1) * 100;
		volts[2] = mcp330x_getVoltage(SINGLE_MODE, 2) * 100;
		volts[3] = mcp330x_getVoltage(SINGLE_MODE, 3) * 100;
		volts[4] = mcp330x_getVoltage(SINGLE_MODE, 4) * 100;
		volts[5] = mcp330x_getVoltage(SINGLE_MODE, 5) * 100;
				
		sprintf(str, "CH0:%3i,CH1:%3i", (int)volts[0], (int)volts[1]);
		sed1565_print(3, 0, str);
		
		sprintf(str, "CH2:%3i,CH3:%3i", (int)volts[2], (int)volts[3]);
		sed1565_print(5, 0, str);
		
		sprintf(str, "CH4:%3i,CH5:%3i", (int)volts[4], (int)volts[5]);
		sed1565_print(7, 0, str);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
