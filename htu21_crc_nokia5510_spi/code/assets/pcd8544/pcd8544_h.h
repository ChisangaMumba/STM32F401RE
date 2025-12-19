#ifndef PCD8544_H
#define	PCD8544_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
#include "../spi/soft_spi.h"
//#include "image.h"
#include "charset.h"
//------------------------------------------------------------------------------
//  Control Pins
#define CS1   							PA3	
#define RS   								PA6			
#define RST   							PA7
//------------------------------------------------------------------------------
#define EXTENDED_COMMANDS   0x21		//use extended instruction set      
#define CONTRAST     				0xC8		//set LCD Vop for contrast
#define TEMP_COEFFIECIENT   0x06		//set temperature coefficient
#define BIAS_MODE    				0x13		//select Bias voltage 
#define BASIC_COMMANDS      0x20		//use basic instruction se
#define ALL_SEGS_ON         0x0C		//set normal mode
//------------------------------------------------------------------------------
#define ROW0								0x40
#define COL0								0x80
//------------------------------------------------------------------------------
#define CLEAR       				0x00
#define FILL        				0xFF
#define SPACE       				CLEAR
//------------------------------------------------------------------------------
void pcd8544_init(void);
void pcd8544_command(uint8_t command);
void pcd8544_setPosition(uint8_t page, uint8_t column);
void pcd8544_print(uint8_t row, uint8_t col, char text[]);
void pcd8544_image(uint8_t *image);
void pcd8544_sendBits(uint8_t data);
void pcd8544_fill(uint8_t data);
void pcd8544_reset(void);
void writeChar(char chr);
inline uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
#endif
