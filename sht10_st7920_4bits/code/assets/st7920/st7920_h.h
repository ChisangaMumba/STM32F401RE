#ifndef LCD8_H
#define	LCD8_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
//  Control Pins
#define RS   PA0			
#define EN   PA1
//------------------------------------------------------------------------------
//  Data Pins
#define D4   PA2			
#define D5   PA3
#define D6   PA4			
#define D7   PA5
//------------------------------------------------------------------------------
//  Data Pins Array
//  This array is used to easily access the data pins in a loop.
const uint8_t data_pins[] = {D4, D5, D6, D7}; // Array of data pins for easy access
//------------------------------------------------------------------------------
//                             Transmission direction
//------------------------------------------------------------------------------
#define LSBFIRST        0
#define MSBFIRST        1
//------------------------------------------------------------------------------
#define display_on      0x0C      //Cursor OFF, Blink off
#define display_off     0x08
#define cursor_on       0x0E
#define cursor_blink    0x0F
#define home            0x02
#define clear           0x01
#define auto_increment  0x06
#define auto_decrement  0x04
#define function_set4   0x28       //DL = 0 <Data Lenghth> (4 bit mode). N = 1 <Num lines> (2 Lines).
#define function_set8   0x38       //function set: 8 bit data length, Two display lines
#define font2           function_set | 0x04     //Set bit 3 only.
//------------------------------------------------------------------------------
void st7920_init(void);
void st7920_transmit(uint8_t data);
void st7920_data(uint8_t data);
void st7920_command(uint8_t command);
void st7920_print(uint8_t row, uint8_t col, const char* format, ...);
void st7920_string(uint8_t row, uint8_t column, char text[]);
void st7920_sendBits(uint8_t data);
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir);
void latch(void);
//------------------------------------------------------------------------------
const uint8_t rowAddr[] = { 0x80, 0x90, 0x88, 0x98 };  
//------------------------------------------------------------------------------
#endif
