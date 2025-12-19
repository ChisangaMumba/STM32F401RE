#ifndef TLC5925_C
#define	TLC5925_C
//------------------------------------------------------------------------------ 
#include "tlc5925_h.h"  
//------------------------------------------------------------------------------
void shiftReg_init(void)
{
	spi_init();
	
	pinMode(CS2, OUTPUT, PUSH_PULL);
	digitalWrite(CS2, HIGH);  // Deselect CS1 initially;
}
//------------------------------------------------------------------------------
void shiftReg_digitSend(uint16_t digit)
{ 
	shiftReg_out(digit >> 8); // Higher byte sent first
	shiftReg_out(digit);			// Lower byte. Truncates upper byte automatically
	shiftReg_latch();
}
//------------------------------------------------------------------------------
void shiftReg_out(uint8_t data)
{	
	for(uint8_t tx = 0; tx < 8; tx++)
	{
		digitalWrite(SCLK, HIGH);       // SCLK = 1;
		digitalWrite(SDOUT, ((data << tx) & 0x80) ? HIGH : LOW);  // MSB first
		digitalWrite(SCLK, LOW);        // SCLK = 0;
	}
}
//------------------------------------------------------------------------------
void shiftReg_latch(void)
{
	digitalWrite(CS2, LOW);   // CS1 = 0;
	digitalWrite(CS2, HIGH);	// CS1 = 1;
}
//------------------------------------------------------------------------------
#endif
