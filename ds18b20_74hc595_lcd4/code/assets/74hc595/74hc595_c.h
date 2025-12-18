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
	
	digitalWrite(CS1, HIGH);  // Deselect CS1 initially;
}
//------------------------------------------------------------------------------
void shiftReg_write(uint8_t data)
{
  digitalWrite(CS1, LOW);   // CS1 = 0; // Chip Select: active low
	
	spi_write(data);
 
  digitalWrite(CS1, HIGH);  // CS1 = 1;
}
//------------------------------------------------------------------------------
#endif
