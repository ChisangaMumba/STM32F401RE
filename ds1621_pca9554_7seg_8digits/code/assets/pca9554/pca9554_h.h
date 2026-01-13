#ifndef PCA9554_H
#define PCA9554_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//-----------------------W/R Control bytes--------------------------------------
#define PORT_IN_REG					0x00
#define PORT_OUT_REG				0x01
#define PORTLARITY_REG			0x02
#define PORT_CONFIG_REG			0x03
//------------------------------------------------------------------------------
void 		 pca9554_init(uint8_t devAddr, uint8_t portState);
void		 pca9554_write(uint8_t devAddr, uint8_t regAddr, uint8_t portData);
uint8_t	 pca9554_read(uint8_t devAddr, uint8_t portAddr, uint8_t pinNo); 
//------------------------------------------------------------------------------
#endif
