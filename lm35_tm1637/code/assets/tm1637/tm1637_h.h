#ifndef TM1637_H
#define TM1637_H
//------------------------------------------------------------------------------
#include "twoWire.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define DISPLAY_MODE  0x40  // Or Keyscan mode 0x42
#define DISPLAY_CTRL  0x87
#define DISPLAY_REG0  0xC0
#define DECIMAL_POINT 0x80
//------------------------------------------------------------------------------
void    tm1637_init(uint8_t level);
void    tm1637_displayNum(long number);
void    tm1637_displayText(char text[]);
void    tm1637_setBrightness(uint8_t brightness);
void    tm1637_write(char text[]);
void    tm1637_command(uint8_t command);
void    tm1637_initSend(uint8_t command);
void    writeChar(char chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(char chr, uint8_t charPos, int8_t dpPos);
void    setDpPos(int8_t dpPos[], char chars[]);
uint8_t isPrint(uint8_t chr);
//------------------------------------------------------------------------------
#endif 
