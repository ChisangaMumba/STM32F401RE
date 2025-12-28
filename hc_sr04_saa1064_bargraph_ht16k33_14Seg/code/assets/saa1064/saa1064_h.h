#ifndef SAA1064_H
#define SAA1064_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//------------------------------------------------------------------------------
#define SAA1064_ADDRESS  0x70      //Address bits can be altered on device if wished
#define CONTROL_REG      0x00      
#define DISPLAY_REG      0x01      
#define DEVICE_CONFIG    0x40      // Static mode 
//------------------------------------------------------------------------------
void saa1064_init(void);
void saa1064_write(uint16_t data);
//------------------------------------------------------------------------------
#endif		/* SAA1064_PROTOTYPES_H */
