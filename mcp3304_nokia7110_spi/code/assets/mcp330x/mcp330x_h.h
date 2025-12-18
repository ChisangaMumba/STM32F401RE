#ifndef MCP330X_H
#define	MCP330X_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define 	CS2		PA4
//------------------------------------------------------------------------------
#define		DIFFERENTIAL_MODE		0x08
#define		SINGLE_MODE	        0x0C
//------------------------------------------------------------------------------
void			mcp330x_init(void);
uint16_t	mcp330x_read(uint8_t mode, uint8_t chn);
float 		mcp330x_getVoltage(uint8_t mode, uint8_t chn);
float 		calcVoltage(uint16_t adcValue);
//------------------------------------------------------------------------------
uint8_t channel[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
//------------------------------------------------------------------------------
#endif
