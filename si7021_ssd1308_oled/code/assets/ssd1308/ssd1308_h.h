#ifndef SSD1308_H
#define SSD1308_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define RST   					PA3
//------------------------------------------------------------------------------
#define SSD1308_I2C_ADDRESS 			0x3C
// SSD1308 Commands
#define SSD1308_DISPLAY_OFF 			0xAE
#define SSD1308_DISPLAY_ON  			0xAF
#define SSD1308_SET_CONTRAST 			0x81
#define SSD1308_DISPLAY_RAM 			0xA4
#define SSD1308_MEMORY_MODE 			0x20
#define SSD1308_SET_PAGE_ADDR 		0xB0
#define SSD1308_SET_COLUMN_ADDR 	0x21
#define SCREEN_WIDTH 							128
#define SCREEN_HEIGHT							64
//------------------------------------------------------------------------------
void ssd1308_init(void);
void ssd1308_command(uint8_t command);
void ssd1308_data(uint8_t data_);
void ssd1308_print(uint8_t row, uint8_t col, char text[]);
void ssd1308_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap);
void ssd1308_reset(void);
inline uint8_t isPrint(char chr);
void writeChar(uint8_t row);
//------------------------------------------------------------------------------
#endif
