#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
#define WAIT 200
//------------------------------------------------------------------------------ 
void i2c_init(uint8_t i2cNum); 
void i2c_setClock(uint8_t i2cNum);
void i2c_setPins(uint8_t i2cNum);
I2C_TypeDef * i2c_getPeripheral(uint8_t i2cNum);
void i2c_start(void); 
void i2c_restart(void);
void i2c_stop(void); 
void i2c_ack(uint8_t ackn); 
void i2c_address(uint8_t address);
void i2c_wait(void);
//uint8_t i2c_write(uint8_t data);
void i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t ackState);
//------------------------------------------------------------------------------
/*
i2c1_scl	PB6		// AF 4
i2c1_sda	PB7		// AF 4

i2c1_scl	PB8		// AF 4
i2c1_sda	PB9		// AF 4

i2c2_scl	PB10	// AF 4
i2c2_sda	PB3		// AF 9

i2c3_scl	PA8		// AF 4
i2c3_sda	PC9		// AF 4
*/
//------------------------------------------------------------------------------
#endif

