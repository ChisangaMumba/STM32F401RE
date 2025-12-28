#ifndef HT16K33_H
#define	HT16K33_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../i2c/soft_i2c.h"
#include "../delay/delay_c.h"
#include "charset.h"
//------------------------------------------------------------------------------
#define HT16K33_ADDRESS  0xE0      //Address bits can be altered on device if wished
#define OSCILLATOR_ON    0x21      //HT16K33 internal oscillator
#define DIGITAL_DIM      0xE0      
#define DISPLAY_SETUP    0x81
#define DISPLAY_MEMORY   0x00      //Start address. auto increments on every write. valid from 0x00 - 0xFF then auto wraps after last valid address
#define DECIMAL_POINT    0x80
//------------------------------------------------------------------------------
void    ht16k33_init(uint8_t brightness);
void    ht16k33_on(void);
void    ht16k33_blink(uint8_t _data);
void    ht16k33_setBrightness(uint8_t _data);
void 		ht16k33_print(const char* format, ...);
void    ht16k33_string(char text[]);
void    ht16k33_write(char text[]);
void    writeChar(char chr, uint8_t chrPos, int8_t dpPos);
uint8_t getDigit(char chr, uint8_t chrPos, int8_t dpPos);
void    setDpPos(int8_t dpPos[], char chars[]);
inline  uint8_t isPrint(char chr);
//------------------------------------------------------------------------------
#endif	/* HT16K33_H */
