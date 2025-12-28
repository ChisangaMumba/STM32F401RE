#ifndef SAA1064_H
#define SAA1064_H
//------------------------------------------------------------------------------
#include <stdarg.h> // Required for variadic functions
#include "../delay/delay_c.h"
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define SAA1064_ADDRESS  0x70      //Address bits can be altered on device if wished
#define CONTROL_REG      0x00      
#define DISPLAY_REG      0x01      
#define DEVICE_CONFIG    0x47      //adds 12 mA to segment output current. dynamic mode 
#define DECIMAL_POINT    0x80
//------------------------------------------------------------------------------
void saa1064_init(void);
void saa1064_print(const char* format, ...);
void saa1064_string(char text[]);
void saa1064_multiData(char data[]);
void writeChar(char chr, uint8_t chrPos, int8_t  dpPos);
uint8_t getDigit(uint8_t charPos, int8_t dpPos, uint8_t chr);
void setDpPos(int8_t dpPos[], char chars[]);
uint8_t getCustomChar(char chrAscii);
inline uint8_t isDigit(char chr);
inline char toUpper(char chr);
inline char toLower(char chr);
void reverseStr(char str[]);
uint8_t strLen(char str[]);
//------------------------------------------------------------------------------
//Common Cathode					 0,    1,    2,    3,    4,    5,    6,    7,    8,   9
//------------------------------------------------------------------------------
const char digits[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
//----------------------------Custom characters---------------------------------
const char customChar[2][10] = 
{
	{  '-',  ' ',  '°',  'C',  'F',  '%',  'E',  'O',  'R', '\0' },
	{ 0x40, 0x00, 0x63, 0x4E, 0x47, 0x67, 0x4F, 0x1D, 0x05, '\0' }  // character code
}; 
//------------------------------------------------------------------------------
#endif		/* SAA1064_PROTOTYPES_H */
