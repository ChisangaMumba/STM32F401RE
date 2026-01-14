#ifndef I2C_C
#define I2C_C
//------------------------------------------------------------------------------
#include "../i2c/i2c_h.h"
#define WAIT 10
//------------------------------------------------------------------------------ 
void i2c_init(void)
{
	/*
  // Note i2c SDA is open drain, this means we need to use INPUT for an SDA high logic. I.e. we can't just write digitalWrite(pin, HIGH) for the SDA.
  pinMode(SCL, OUTPUT, PUSH_PULL, NO_PU_PD);

  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP); 		// SDA = 1
  digitalWrite(SCL, HIGH);   										// SCL = 1
	*/
	// Enable GPIOB
  //RCC->AHB1ENR |= (1 << 1);
	
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // i2c1 enable
	
	/*
	// Alternative Function: i2c1, i2c2, i2c3 is 4. i2c2, i2c3 or 9 (or 4 as well, as stated earlier), see "Table 9: Alternate function mapping" of datasheet
	pinAltFunc(SCL, OPEN_DRAIN, NO_PU_PD, 4);
	pinAltFunc(SDA, OPEN_DRAIN, NO_PU_PD, 4);
	*/
	///*
	// Alternative Function: i2c1, i2c2, i2c3 is 4. i2c2, i2c3 or 9 (or 4 as well, as stated earlier), see "Table 9: Alternate function mapping" of datasheet
	pinAltFunc(SCL, OPEN_DRAIN, PULL_UP, 4);
	pinAltFunc(SDA, OPEN_DRAIN, PULL_UP, 4);
	//*/
	
	/*
	I2C1->CR1 |= I2C_CR1_SWRST;				// 1 = Reset i2c1
	I2C1->CR1 &= ~(I2C_CR1_SWRST);		// Complete the reset
	
	//I2C1->CR2 = I2C_CR2_FREQ_4;				// Select peripheral clock frequency // PCLK1 = 16 MHz -> CR2 = 16
	
	// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	I2C1->CR2 |= (45<<0);  // PCLK1 FREQUENCY in MHz
	
	// Configure the clock control registers
	I2C1->CCR = 225; 								// CCR = PCLK1 / (2 * 100k) = 80
	
	I2C1->TRISE = 46;								// TRISE = (PCLK1/1MHz) + 1 = 17
	
	I2C1->CR1 |= I2C_CR1_PE;					// Enable i2c1
	*/
	I2C1->CR1 |= I2C_CR1_SWRST;				// 1 = Reset i2c1
	I2C1->CR1 &= ~(I2C_CR1_SWRST);		// Complete the reset
	
	I2C1->CR2 = I2C_CR2_FREQ_4;				// Select peripheral clock frequency // PCLK1 = 16 MHz -> CR2 = 16
	
	I2C1->CCR = 0x50; 								// CCR = PCLK1 / (2 * 100k) = 80
	
	I2C1->TRISE = 0x11;								// TRISE = (PCLK1/1MHz) + 1 = 17
	
	I2C1->CR1 |= I2C_CR1_PE;					// Enable i2c1	
}
//------------------------------------------------------------------------------ 
void i2c_start(void)
{
	/*
  pinMode(SDA, OUTPUT, OPEN_DRAIN, PULL_UP);  	// SDA = 0
  digitalWrite(SCL, LOW);   										// SCL = 0
	*/
	/*
	i2c_ack(ACK);
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));	// Wait fror SB bit to set
	*/
	/*
	I2C1->CR1 |= (1<<10);  // Enable the ACK
	I2C1->CR1 |= (1<<8);  // Generate START
	while (!(I2C1->SR1 & (1<<0)));  // Wait fror SB bit to set
	*/
	/*
	uint16_t count = 0;
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB) && (count++ < WAIT)) delay_us(1);
	if(count >= WAIT) return ;
	//i2c_ack(ACK);
	*/
	/*
	I2C1->CR1 |= I2C_CR1_START;
	i2c_wait();
	*/
	//I2C1->CR1 |= (1<<10);  // Enable the ACK
	I2C1->CR1 |= I2C_CR1_START;
	while(!(I2C1->SR1 & I2C_SR1_SB));
}
//------------------------------------------------------------------------------ 
void i2c_restart(void)
{
	/*
  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP);   	// SDA = 1
  digitalWrite(SCL, HIGH);   										// SCL = 1
  pinMode(SDA, OUTPUT, OPEN_DRAIN, PULL_UP);  	// SDA = 0
  digitalWrite(SCL, LOW);    										// SCL = 0
	*/
	i2c_start();
}
//------------------------------------------------------------------------------ 
void i2c_stop(void)
{
	/*
  digitalWrite(SCL, LOW);    										// SCL = 0
  pinMode(SDA, OUTPUT, OPEN_DRAIN, PULL_UP);  	// SDA = 0
  digitalWrite(SCL, HIGH);   										// SCL = 1
  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP);   	// SDA = 1
	*/
	/*
	uint16_t count = 0;
	I2C1->CR1 |= I2C_CR1_STOP;
	while(!(I2C1->SR1 & I2C_SR1_STOPF)) delay_us(1);
	if(count >= WAIT) return;
	*/
	/*
	I2C1->CR1 |= I2C_CR1_STOP;  // Stop I2C
	i2c_wait();
	*/
	I2C1->CR1 |= I2C_CR1_STOP;
	while(!(I2C1->SR1 & I2C_SR1_STOPF));
}
//------------------------------------------------------------------------------ 
void i2c_ack(uint8_t ackn)
{
	/*
  pinMode(SDA, (ackn == 1) ? INPUT : OUTPUT, OPEN_DRAIN, PULL_UP);  // SDA = ackn; 
  digitalWrite(SCL, HIGH);                      										// SCL = 1
  digitalWrite(SCL, LOW);                       										// SCL = 0
  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP);                         // SDA = 1
	*/
	/*
	//																	ACK														NACK
	I2C1->CR1 = (ackn == 0) ? (I2C1->CR1 | I2C_CR1_ACK) : (I2C1->CR1 & (~I2C_CR1_ACK));	
	*/
	///*
	if(ackn == 0)
	{
		I2C1->CR1 |= I2C_CR1_ACK;					// ACKnowledge	
	}
	else
			if(ackn == 1)
			{
				I2C1->CR1 &= ~I2C_CR1_ACK;		// NOT ACKnowledge	
			}
	//*/
}
//------------------------------------------------------------------------------ 
void i2c_wait(void)
{
	// Wait until i2c bus is ready
	while ((I2C1->SR2 & I2C_SR2_BUSY) == I2C_SR2_BUSY);
}
//------------------------------------------------------------------------------ 
void i2c_address(uint8_t address)
{
	/*
	uint16_t count = 0;
	
	I2C1->DR = address;
	
	while (!(I2C1->SR1 & I2C_SR1_ADDR) && (count++ < WAIT)) delay_us(1);  // Wait for ADDR bit to be set
	if(count >= WAIT) return;
	
	uint8_t temp = I2C1->SR1 | I2C1->SR2; // read SR1 and SR2 to clear the ADDR bit
	*/
	/*
	I2C1->DR = address;
	while (!(I2C1->SR1 & 2));  // Wait ADDR
	volatile uint32_t temp = I2C1->SR1 | I2C1->SR2; // Clear ADDR flag
	(void)temp;	
	*/
	/*
	I2C1->DR = address;
	i2c_wait();
	
	uint8_t temp = I2C1->SR1 | I2C1->SR2; // read SR1 and SR2 to clear the ADDR bit
	(void)temp;	
	*/
	
	I2C1->DR = address;
	while(!(I2C1->SR1 & I2C_SR1_ADDR));  	// Wait for ADDR bit to be set
	i2c_ack(ACK);
	
	uint8_t temp = I2C1->SR1 | I2C1->SR2; // read SR1 and SR2 to clear the ADDR bit
}
//------------------------------------------------------------------------------ 
uint8_t i2c_write(uint8_t data)
{	
	/*
  for(uint8_t tx = 0; tx < 8; tx++)
  {
    pinMode(SDA, ((data << tx) & 0x80) ? INPUT : OUTPUT, OPEN_DRAIN, PULL_UP) ; //MSB first SDAT 1 or 0
    digitalWrite(SCL, HIGH);   // SCL = 1
    digitalWrite(SCL, LOW);    // SCL = 0 // Toggle SCK pin So that slave can latch data bit                   
  }
	
  i2c_ack(ACK);
	
  return SDA;
	*/
	/*
	uint16_t count = 0;
	
	while(!(I2C1->SR1 & I2C_SR1_TXE) && (count++ < WAIT)) delay_us(1);	// wait for TXE bit to set
	if(count >= WAIT) return 0;
	
	I2C1->DR = data;
	
	while(!(I2C1->SR1 & I2C_SR1_BTF) && (count++ < WAIT)) delay_us(1);	// Byte wait for BTF bit to set
	if(count >= WAIT) return 0;
	
	i2c_ack(ACK);
	
	return (I2C1->CR1 & I2C_CR1_ACK) ? 1 : 0;
	*/
	/*
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	I2C1->DR = data;
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF bit to set
	
	i2c_ack(ACK);
	
	return (I2C1->CR1 & I2C_CR1_ACK) ? 1 : 0;
	*/
	/*
	while(!(I2C1->SR1 & I2C_SR1_TXE));	// wait for TXE bit to set
	I2C1->DR = data;
	while(!(I2C1->SR1 & I2C_SR1_BTF));	// Byte wait for BTF bit to set
	
	i2c_ack(ACK);
	*/
	///*
	while(!(I2C1->SR1 & I2C_SR1_TXE));	// wait for TXE bit to set
	//i2c_wait();
	I2C1->DR = data;
	//i2c_wait();
	while(!(I2C1->SR1 & I2C_SR1_BTF));	// wait for BTF bit to set (Byte Transfer Finished)
	
	i2c_ack(ACK);
	
	return (I2C1->CR1 & I2C_CR1_ACK) ? 1 : 0;
	//*/
}
//------------------------------------------------------------------------------ 
uint8_t i2c_read(uint8_t ackState)
{
	/*
	uint8_t data = 0;

	for(uint8_t rx = 0; rx < 8; rx++) 
	{
		digitalWrite(SCL, HIGH);   // SCLK = 1
    data += digitalRead(SDA) << (7-rx);  // MSB first
		digitalWrite(SCL, LOW);    // SCLK = 0
	}
	
	i2c_ack(ackState);
	
	return data;
	*/
	
	/*
	uint16_t count = 0;
	while(!(I2C1->SR1 & I2C_SR1_RXNE) && (count++ < WAIT)) delay_us(1);
	if(count >= WAIT) return 0;
	uint8_t data = I2C1->DR;
	
	i2c_ack(ackState);
	
	return data;
	*/
	/*
	i2c_wait();
	uint8_t data = I2C1->DR;
	i2c_wait();
	
	i2c_ack(ackState);
	
	return data;	
	*/
	i2c_ack(ackState);
	
	while(!(I2C1->SR1 & I2C_SR1_RXNE));
	uint8_t data = I2C1->DR;
	
	return data;
}
//------------------------------------------------------------------------------
#endif

