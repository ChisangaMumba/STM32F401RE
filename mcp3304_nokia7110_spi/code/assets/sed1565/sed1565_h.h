#ifndef SED1565_H
#define	SED1565_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
#include "../spi/soft_spi.h"
//#include "image.h"
#include "charset.h"
//------------------------------------------------------------------------------
//  Control Pins
#define CS1   					PA3	
#define RS   						PA6			
#define RST   					PA7
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
inline void sed1565_startLine(uint8_t line);
void sed1565_setPosition(uint8_t page, uint8_t column);
void sed1565_print(uint8_t row, uint8_t col, char text[]);
void sed1565_image(uint8_t *image);
void sed1565_sendBits(uint8_t data);
void sed1565_reset(void);
void writeChar(char chr);
inline uint8_t isPrint(char chr);
void latch(void);
//------------------------------------------------------------------------------
#endif
