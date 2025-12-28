#ifndef SHIFT_REG_C
#define	SHIFT_REG_C
//------------------------------------------------------------------------------
#include "75hc595_h.h"
//------------------------------------------------------------------------------
void shiftReg_init(void)
{   
	spi_init();
	
	pinMode(CS1, OUTPUT, PUSH_PULL);
  pinMode(CS2, OUTPUT, PUSH_PULL);
}
//------------------------------------------------------------------------------
void shiftReg_control(uint8_t control)
{	
	spi_write(control);
	
	digitalWrite(CS1, LOW);			// CS1 = 0;
	digitalWrite(CS1, HIGH);		// CS1 = 1;
}
//------------------------------------------------------------------------------
void shiftReg_data(uint8_t data)
{	
	spi_write(data);
	
	digitalWrite(CS2, LOW);			// CS2 = 0;
	digitalWrite(CS2, HIGH);		// CS2 = 1;
}
//------------------------------------------------------------------------------
#endif
