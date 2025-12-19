#ifndef MAX6950_H
#define	MAX6950_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
//------------------------------------------------------------------------------
#define CS1  PA3
#define CS2  PA4
//------------------------------------------------------------------------------
uint8_t chips[] = {CS1, CS2};
//------------------------------------------------------------------------------
//													Max6954 Register
//------------------------------------------------------------------------------
#define DECODE_MODE_REG     0x01
#define INTESITY_REG        0x02
#define SCAN_LIMIT_REG      0x03
#define SHUTDOWN_REG        0x04
#define DISPLAY_TEST_REG    0x07
#define DIGIT_TYPE_REG      0x0C
//------------------------------------------------------------------------------
//													Max6954 Commands
//------------------------------------------------------------------------------
#define DISABLE_DECODE      0x00
#define DECODE_ALL          0xFF
#define BRIGHTNESS          0xFF
#define MODE_14_SEG         0xFF
#define SCAN_LIM0		     		0x00	// Display digit  0 only
#define SCAN_LIM1     			0x01	// Display digits 0 and 1
#define SCAN_LIM2     			0x02	// Display digits 0 and 1 2
#define SCAN_LIM3     			0x03	// Display digits 0 and 1 2 3
#define SCAN_LIM4     			0x04	// Display digits 0 and 1 2 3 4
#define SCAN_LIM5     			0x05	// Display digits 0 and 1 2 3 4 5
#define SCAN_LIM6     			0x06	// Display digits 0 and 1 2 3 4 5 6
#define SCAN_ALL_DIGITS     0x07	// Display digits 0 and 1 2 3 4 5 6 7
//
#define SHUTDOWN_MODE       0x00
#define NORMAL_OPERATION    0x01
#define DISABLE_TEST_MODE   0x00
#define ENABLE_TEST_MODE    0x01
#define DECIMAL_POINT       0x80
#define DISPLAY_REG0        0x20
//------------------------------------------------------------------------------
//															Max6952 Prototypes
//------------------------------------------------------------------------------
void 		max6954_init(uint8_t noChips);
void 		max6954_config(uint8_t chip);
void 		max6954_write(uint8_t reg, uint8_t data, uint8_t chip);
void 		max6954_displayNumber(long number);
void 		max6954_displayText(char text[]);
void 		writeChar(char chr, uint8_t chrPos, int8_t  dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void 		setDpPos(int8_t dpPos[], char chars[]);
uint8_t getCustomChar(char chrAscii);
inline  uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
char customChar[] = "£¥€°µ±";             //see Max6954 datasheet page 13 (Table 14. Character Map)
char charCode[] = {24,25,26,27,28,29};
//------------------------------------------------------------------------------
#endif
