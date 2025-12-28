#ifndef SED1565_H
#define	SED1565_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
#include "../spi/soft_spi.h"
//------------------------------------------------------------------------------
//  Control Pins
#define CS1   PA3	
//------------------------------------------------------------------------------
// 							ST7290 Command Set (refer to the ST7290 datasheet)
//------------------------------------------------------------------------------
#define display_on      0xAF      
#define display_off     0xAE
#define display_clear   0x01
#define set_ddram     	0x80
//------------------------------------------------------------------------------
const uint8_t rowAddr[] = { 0x80, 0x90, 0x88, 0x98 };
//------------------------------------------------------------------------------
void st7920_init(void);
void st7920_data(uint8_t data);
void st7920_command(uint8_t command);
void st7920_print(uint8_t row, uint8_t col, const char* format, ...);
void st7920_string(uint8_t row, uint8_t col, char text[]);
//------------------------------------------------------------------------------
#endif
