#ifndef SHIFT_REG_C
#define SHIFT_REG_C
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define CS1   PA3          
//------------------------------------------------------------------------------
void shiftReg_init(void)
{
	spi_init();
	pinMode(CS1, OUTPUT, PUSH_PULL);
}
//------------------------------------------------------------------------------
void shiftReg_write(uint8_t data)
{
	spi_write(data);
	
  digitalWrite(CS1, HIGH);  // CS1 = 1;
	digitalWrite(CS1, LOW);   // CS1 = 0; 
}
//------------------------------------------------------------------------------
#endif
