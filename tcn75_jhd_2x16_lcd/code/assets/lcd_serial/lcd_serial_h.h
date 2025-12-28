#ifndef LCD_SERIAL_H
#define LCD_SERIAL_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define display_on      0x0C      // Cursor OFF, Blink off
#define display_off     0x08
#define cursor_on       0x0E
#define cursor_blink    0x0F
#define home            0x02
#define clear           0x01
#define auto_increment  0x06
#define auto_decrement  0x04
#define function_set4   0x28       // DL = 0 <Data Lenghth> (4 bit mode). N = 1 <Num lines> (2 Lines).
#define function_set8   0x38       // function set: 8 bit data length, Two display lines
#define font2a          function_set4 | 0x04     //Set bit 3 only.
#define font2b          function_set8 | 0x04
//------------------------------------------------------------------------------
uint8_t  RowAddr[] = {0x80,0xC0,0x94,0xD4}; //Row0-Row3
//------------------------------------------------------------------------------
#define CMD_REG         0x80			// C0=1 RS=0 (Instruction Register ( commands ))           
#define DAT_REG         0x40			// C0=0 RS=0 Data Register (Strings and characters).	  
#define DEV_ADDR        0x7C			// See JHD1214 datasheet  
//------------------------------------------------------------------------------
void lcd_init(void);
void lcd_setPos(uint8_t data);
void lcd_command(uint8_t data);
void lcd_print(uint8_t row, uint8_t col, const char* format, ...);
void lcd_string(uint8_t row, uint8_t col, char text[]);
//------------------------------------------------------------------------------
#endif
