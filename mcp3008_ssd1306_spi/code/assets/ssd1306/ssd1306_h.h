#ifndef SSD1306_H
#define SSD1306_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../spi/soft_spi.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define CS1		PA3
#define DC		PA6
#define RST		PA7
//------------------------------------------------------------------------------
// SSD1306 Commands
#define SSD1306_DISPLAY_OFF 			0xAE
#define SSD1306_DISPLAY_ON  			0xAF
#define SSD1306_SET_CONTRAST 			0x81
#define SSD1306_DISPLAY_RAM 			0xA4
#define SSD1306_MEMORY_MODE 			0x20
#define SSD1306_SET_PAGE_ADDR 		0xB0
#define SSD1306_SET_COLUMN_ADDR 	0x21
#define SCREEN_WIDTH 							128
#define SCREEN_HEIGHT							64
//------------------------------------------------------------------------------
void ssd1306_init(void);
void ssd1306_command(uint8_t command);
void ssd1306_data(uint8_t data_);
void ssd1306_print(uint8_t row, uint8_t col, char text[]);
void ssd1306_displayImage(uint16_t width, uint16_t height, const uint8_t *bitmap);
inline uint8_t isPrint(char chr);
void writeChar(uint8_t row);
void ssd1306_reset(void);
//------------------------------------------------------------------------------
#endif
