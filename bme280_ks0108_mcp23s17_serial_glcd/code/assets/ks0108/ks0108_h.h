#ifndef KS0108_H
#define	KS0108_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../spi/soft_spi.h"
#include "../delay/delay_c.h"
#include "../mcp23s17/mcp23s17_c.h"
#include "charset.h"
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
void ks0108_image(const uint8_t *image);
void ks0108_setAddress(uint8_t row, uint8_t col);
void ks0108_column(uint16_t col);
void ks0108_fill(uint8_t fill);
void ks0108_chip(uint8_t chip);
void ks0108_latch(uint8_t data);
void writeChar(uint8_t fontNo, char chr);
inline uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
#define EN_HIGH   0x02
#define EN_LOW    0xFD
//------------------------------------------------------------------------------
const uint8_t rowAddr[8] = {0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0xBE,0xBF}; // GLCD Pages addresses
uint8_t column = 0;  
uint8_t CS = 0;   // Chip Select 
uint8_t RS = 0;		// Register Select  
//------------------------------------------------------------------------------
#endif
