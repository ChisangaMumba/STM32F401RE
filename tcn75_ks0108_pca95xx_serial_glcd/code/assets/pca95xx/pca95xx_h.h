#ifndef PCA95xx_H
#define PCA95xx_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
//-----------------------W/R Control bytes--------------------------------------
#define WRITE      					0x40   // 0b0100 + 0b0(Slave address) + 0b0(Write) => 0x40
#define READ       					0x41

#define PORTA_WR						0x02
#define PORTA_RD						0x00
#define PORTB_WR						0x03
#define PORTB_RD						0x01

#define PORTA_CONFIG				0x06
#define PORTB_CONFIG				0x07
//------------------------------------------------------------------------------
void     pca95xx_init(uint8_t portStateA, uint8_t portStateB);
void		 pca95xx_write8(uint8_t regAddr, uint8_t portData);
void		 pca95xx_write16(uint8_t regAddr, uint8_t portA_data, uint8_t portB_data);
uint8_t  pca95xx_read8(uint8_t portAddr);
uint16_t pca95xx_read16(void); 
//------------------------------------------------------------------------------
#endif
