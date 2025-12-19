#ifndef SHT7x_H
#define	SHT7x_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
// Define the SHT7x I/O pins (adjust as needed)
#define 	SHT_CLK  						PA11  		// SHT7x clock
#define 	SHT_DATA 						PA12			// SHT7x data (bidirectional)
//------------------------------------------------------------------------------
#define 	TEMP_CMD  					0x03
#define 	HUMD_CMD  					0x05
#define 	WR_STATUS_REG_CMD  	0x06
#define 	RD_STATUS_REG_CMD  	0x07
#define 	SOFT_RESET_CMD  		0x1E
#define 	TIMEOUT_LIMIT 			10000
//------------------------------------------------------------------------------
#define 	SHT_ACK  						0
#define 	SHT_NACK 						1
//------------------------------------------------------------------------------
void 			SBus_start(void);
uint8_t 	SBus_ack(uint8_t ack);
uint8_t 	SBus_write(uint8_t data_);
uint8_t 	SBus_read(uint8_t ack);
uint8_t 	SBus_waitForResult(void);
void 			sht7x_init(void);
uint16_t 	sht7x_read(uint8_t command);
float 		sht7x_getTemp(void);
float 		sht7x_getHumd(float tempr);
//------------------------------------------------------------------------------
#endif
