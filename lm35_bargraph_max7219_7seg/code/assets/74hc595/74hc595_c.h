#ifndef SHIFT_REG_C
#define SHIFT_REG_C
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
#define CS2	PA4          
//------------------------------------------------------------------------------
void shiftReg_init(void)
{
	spi_init();
	pinMode(CS2, OUTPUT, PUSH_PULL, NO_PU_PD);
	
	digitalWrite(CS2, HIGH);  // Deselect CS1 initially;
}
//------------------------------------------------------------------------------
void shiftReg_write(uint8_t data)
{
	spi_write(data);
 
	digitalWrite(CS2, LOW);   // CS2 = 0;
	delay_us(1);
	digitalWrite(CS2, HIGH);  // CS2 = 1;
}
//------------------------------------------------------------------------------
#endif
