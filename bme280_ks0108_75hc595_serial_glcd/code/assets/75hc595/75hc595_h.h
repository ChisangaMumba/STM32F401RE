#ifndef SHIFT_REG_H
#define	SHIFT_REG_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define CS1 PA3
#define CS2 PA4
//------------------------------------------------------------------------------
void shiftReg_init(void);
void shiftReg_control(uint8_t control);
void shiftReg_data(uint8_t data);
//------------------------------------------------------------------------------
#endif
