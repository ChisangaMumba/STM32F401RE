#ifndef SED1565_H
#define	SED1565_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
// #include "image.h"
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
//  Data Pins Array
//  This array is used to easily access the data pins in a loop.
const uint8_t data_pins[] = {D0, D1, D2, D3, D4, D5, D6, D7}; // Array of data pins for easy access
//------------------------------------------------------------------------------
//                             Transmission direction
//------------------------------------------------------------------------------
#define LSBFIRST        0
#define MSBFIRST        1
//------------------------------------------------------------------------------
#define CLEAR       		0x00
#define FILL        		0xFF
#define pgLen       		8
#define pgWidth     		128
//------------------------------------------------------------------------------
#define display_on      0xAF      
#define display_off     0xAE
#define bg_white  			0xA6	// bg Background white	
#define bg_black				0xA7	// bg Background black	
#define adc_normal      0xA1	// ADC (Address Counter) Selection: Normal.
#define adc_reverse    	0xA0	// ADC (Address Counter) Selection: reverse.
#define reset           0xE2
//------------------------------------------------------------------------------
void sed1565_init(void);
void sed1565_data(uint8_t data);
void sed1565_command(uint8_t command);
void sed1565_startLine(uint8_t line);
void sed1565_setPosition(uint8_t page, uint8_t column);
void sed1565_print(uint8_t row, uint8_t col, char text[]);
void sed1565_image(uint8_t *image);
void sed1565_sendBits(uint8_t data);
void writeChar(char chr);
uint8_t getBit(uint8_t pos , uint8_t data, uint8_t dir);
inline uint8_t isPrint(char chr);
void latch(void);
//------------------------------------------------------------------------------
#endif
