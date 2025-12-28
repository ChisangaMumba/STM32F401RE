#ifndef KS0108_H
#define	KS0108_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
#include "image.h"
#include "charset.h"
//------------------------------------------------------------------------------
//  Control Pins
#define RS   PA0			
#define EN   PA1
//------------------------------------------------------------------------------
//  Data Pins
#define D0   PA2			
#define D1   PA3
#define D2   PA4			
#define D3   PA5
#define D4   PA6			
#define D5   PA7
#define D6   PA8			
#define D7   PA9
//------------------------------------------------------------------------------
#define CS1  PA11			
#define CS2  PA12
//------------------------------------------------------------------------------
//  Data Pins Array
//  This array is used to easily access the data pins in a loop.
const uint8_t data_pins[] = {D7, D6, D5, D4, D3, D2, D1, D0}; // Array of data pins for easy access arranged in MSB format
//const uint8_t data_pins[] = {D0, D1, D2, D3, D4, D5, D6, D7}; // Array of data pins for easy access arranged in LSB format
//------------------------------------------------------------------------------
//                             Transmission direction
//------------------------------------------------------------------------------
#define LSBFIRST        0
#define MSBFIRST        1
//------------------------------------------------------------------------------
#define display_on      0x3F      
#define display_off     0x3E
//------------------------------------------------------------------------------
#define glcdWidth   		128      //128 bits since 128 x 64
#define pgWidth     		64       //64 bits on chip1 and chip2 each
#define pgLen       		8        //8 Bits
#define CLEAR       		0x00
#define FILL        		0xFF
#define font1        		0x00
#define font2        		0x01
//------------------------------------------------------------------------------
void ks0108_init(void);
void ks0108_data(uint8_t data, uint8_t chipNo);
void ks0108_command(uint8_t command, uint8_t chipNo);
void ks0108_print(uint8_t row, uint8_t col, uint8_t fontNo, const char* format, ...);
void ks0108_string(uint8_t row, uint8_t col, uint8_t fontNo, char text[]);
void ks0108_bitmap(const uint8_t *bitmap, int elements);
void ks0108_sendBits(uint8_t data);
void ks0108_image(const uint8_t *image);
void ks0108_setAddress(uint8_t row, uint8_t col);
void ks0108_column(uint16_t col);
void ks0108_fill(uint8_t fill);
void ks0108_chip(uint8_t chip);
void writeChar(uint8_t fontNo, char chr);
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir);
void latch(void);
inline uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
unsigned char rowAddr[8] = { 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF }; // GLCD Pages addresses
unsigned int  column = 0;  
//------------------------------------------------------------------------------
#endif
