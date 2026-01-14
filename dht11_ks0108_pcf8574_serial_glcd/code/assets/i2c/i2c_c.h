#ifndef I2C_C
#define I2C_C
//------------------------------------------------------------------------------
#include "../i2c/i2c_h.h"
//------------------------------------------------------------------------------
static I2C_TypeDef * I2Cx;
//------------------------------------------------------------------------------ 
void i2c_init(uint8_t i2cNum)
{	
	i2c_setClock(i2cNum);
	i2c_setPins(i2cNum);
	I2Cx = i2c_getPeripheral(i2cNum);
	
	// Reset I2Cx device
	I2Cx->CR1 |= I2C_CR1_SWRST;					// 1 = Reset I2Cx
	I2Cx->CR1 &= ~(I2C_CR1_SWRST);			// Complete the reset
	
	// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	I2Cx->CR2 |= (45<<0);  							// PCLK1 FREQUENCY in MHz
	
	// Configure the clock control registers
	I2Cx->CCR = 225; 										// CCR = PCLK1 / (2 * 100k) = 80
	
	I2Cx->TRISE = 46;										// TRISE = (PCLK1/1MHz) + 1 = 17
	
	I2Cx->CR1 |= I2C_CR1_PE;						// Enable I2Cx
}
//------------------------------------------------------------------------------ 
void i2c_setClock(uint8_t i2cNum)
{
	switch(i2cNum)
	{
		case(1): RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; break;  // Enable I2C1 Clock
		#ifdef I2C2
		case(2): RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; break;  // Enable I2C2 Clock
		#endif
		#ifdef I2C3
		case(3): RCC->APB1ENR |= RCC_APB1ENR_I2C3EN; break;  // Enable I2C3 Clock
		#endif
		default: RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	}
}
//------------------------------------------------------------------------------ 
void i2c_setPins(uint8_t i2cNum)
{
	const uint8_t altFunc = 4; // see Figure 17. Selecting an alternate function on STM32F401xB/C and STM32F401xD/E of reference manual
	
	switch(i2cNum)
	{
		case(1):	// I2C1 pins
		{
			pinAltFunc(PB6, OPEN_DRAIN, PULL_UP, altFunc);		//	SCL
			pinAltFunc(PB7, OPEN_DRAIN, PULL_UP, altFunc);		//	SDA
			break;
		}   
		case(2):	// I2C2 pins
		{
			pinAltFunc(PB10, OPEN_DRAIN, PULL_UP, altFunc);		//	SCL
			pinAltFunc(PB3,  OPEN_DRAIN, PULL_UP, 9);					//	SDA
			break;
		}  
		case(3):	// I2C3 pins
		{
			pinAltFunc(PA8, OPEN_DRAIN, PULL_UP, altFunc);		//	SCL
			pinAltFunc(PC9, OPEN_DRAIN, PULL_UP, altFunc);		//	SDA
			break;		
		} 
		default: // I2C1 using alternative pins
		{
			pinAltFunc(PB8, OPEN_DRAIN, PULL_UP, altFunc);		//	SCL
			pinAltFunc(PB9, OPEN_DRAIN, PULL_UP, altFunc);		//	SDA
			break;
		} 
	}
}
//------------------------------------------------------------------------------
I2C_TypeDef * i2c_getPeripheral(uint8_t i2cNum)
{
	I2C_TypeDef * I2Cx;
	
	switch(i2cNum)
	{
		case(1): I2Cx = I2C1; break;  // I2C1
		#ifdef I2C2
		case(2): I2Cx = I2C2; break;  // I2C2
		#endif
		#ifdef I2C3
		case(3): I2Cx = I2C3; break;  // I2C3
		#endif
		default: I2Cx = I2C1;
	}
	
	return I2Cx;
}
//------------------------------------------------------------------------------ 
void i2c_start(void)
{
	uint16_t count = 0;
	
	I2Cx->CR1 |= I2C_CR1_START;
	while(!(I2Cx->SR1 & I2C_SR1_SB) && (count++ < WAIT)) delay_us(1);
	if(count >= WAIT) return ;
}
//------------------------------------------------------------------------------ 
void i2c_restart(void)
{
	i2c_start();
}
//------------------------------------------------------------------------------ 
void i2c_stop(void)
{
	uint16_t count = 0;
	
	I2Cx->CR1 |= I2C_CR1_STOP;
	while(!(I2Cx->SR1 & I2C_SR1_STOPF) && (count++ < WAIT)) delay_us(1);
	if(count >= WAIT) return;
}
//------------------------------------------------------------------------------ 
void i2c_ack(uint8_t ackn)
{
	if(ackn == 0)
	{
		I2Cx->CR1 |= I2C_CR1_ACK;					// ACKnowledge	
	}
	else
			if(ackn == 1)
			{
				I2Cx->CR1 &= ~I2C_CR1_ACK;		// NOT ACKnowledge	
			}
}
//------------------------------------------------------------------------------ 
void i2c_wait(void)
{
	// Wait until i2c bus is ready
	while ((I2Cx->SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY);
}
//------------------------------------------------------------------------------ 
void i2c_address(uint8_t address)
{
	uint16_t count = 0;
	
	I2Cx->DR = address;
	
	// Wait for ADDR bit to be set
	while (!(I2Cx->SR1 & I2C_SR1_ADDR) && (count++ < WAIT)) delay_us(1);  
	if(count >= WAIT) return;
	
	uint8_t temp = I2Cx->SR1 | I2Cx->SR2; // read SR1 and SR2 to clear the ADDR bit
	(void)temp;
}
//------------------------------------------------------------------------------ 
uint8_t i2c_write(uint8_t data)
{	
	uint16_t count = 0;
	
	while(!(I2Cx->SR1 & I2C_SR1_TXE) && (count++ < WAIT)) delay_us(1);	// wait for TXE bit to set
	if(count >= WAIT) return 0;
	
	I2Cx->DR = data;
	
	while(!(I2Cx->SR1 & I2C_SR1_BTF) && (count++ < WAIT)) delay_us(1);	// Byte wait for BTF bit to set
	if(count >= WAIT) return 0;
	
	i2c_ack(ACK);
	
	return (I2Cx->CR1 & I2C_CR1_ACK) ? 1 : 0;
}
//------------------------------------------------------------------------------ 
uint8_t i2c_read(uint8_t ackState)
{
	uint16_t count = 0;
	
	while(!(I2Cx->SR1 & I2C_SR1_RXNE) && (count++ < WAIT)) delay_us(1);
	if(count >= WAIT) return 0;
	uint8_t data = I2Cx->DR;
	
	i2c_ack(ackState);
	
	return data;
}
//------------------------------------------------------------------------------
#endif

