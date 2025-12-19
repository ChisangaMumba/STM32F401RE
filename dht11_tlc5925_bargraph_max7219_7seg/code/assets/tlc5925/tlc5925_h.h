#ifndef TLC5925_H
#define	TLC5925_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define CS2  PA4 
//------------------------------------------------------------------------------
void shiftReg_init(void);
void shiftReg_digitSend(uint16_t digit);
void shiftReg_out(uint8_t data);
void shiftReg_latch(void);
//------------------------------------------------------------------------------
#endif
