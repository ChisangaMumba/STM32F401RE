#ifndef SPI_C
#define	SPI_C
//------------------------------------------------------------------------------
#include "../spi/spi_h.h"
//------------------------------------------------------------------------------
SPI_TypeDef * SPIx;
//------------------------------------------------------------------------------
void spi_init(uint8_t spiNum)
{
	spi_setClock(spiNum);
	
	SPIx = spi_getPeripheral(spiNum);
	// SPI Configuration Register 1
	SPIx->CR1 |= SPI_CR1_CPHA;			//	Clock Phase = 1. The second clock transition is the first data capture edge
	SPIx->CR1 |= SPI_CR1_CPOL;			//	Clock Polarity = 1. CK to 1 when idle
	SPIx->CR1 |= SPI_CR1_MSTR;			//	Master Mode
	SPIx->CR1 |= 0x01UL << 3;				//	BR[2:0] = 001: fPCLK/4, PCLK2 = 16MHz, SPI clk = 4MHz
	SPIx->CR1 &= ~SPI_CR1_LSBFIRST;	//	0: MSB transmitted first
	SPIx->CR1 |= SPI_CR1_SSI;				//	Internal slave select
	SPIx->CR1 |= SPI_CR1_SSM;				//	1: Software slave management enabled
	SPIx->CR1 &= ~SPI_CR1_RXONLY;		//	0: Full duplex (Transmit and receive)
	SPIx->CR1 &= ~SPI_CR1_DFF;			//	Data Frame Format. 0: 8-bit data frame format is selected for transmission/reception
	SPIx->CR1 |= SPI_CR1_SPE;				//	SPE=1, Peripheral enabled
	
	spi_setPins(spiNum);
}
//------------------------------------------------------------------------------
void spi_setClock(uint8_t spiNum)
{
	switch(spiNum)
	{
		case(1): RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; break;  // Enable SPI1 Clock
		#ifdef SPI2
		case(2): RCC->APB1ENR |= RCC_APB1ENR_SPI2EN; break;  // Enable SPI2 Clock
		#endif
		#ifdef SPI3
		case(3): RCC->APB1ENR |= RCC_APB1ENR_SPI3EN; break;  // Enable SPI3 Clock
		#endif
		#ifdef SPI4
		case(4): RCC->APB2ENR |= RCC_APB2ENR_SPI4EN; break;  // Enable SPI4 Clock
		#endif
		default: RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	}
}
//------------------------------------------------------------------------------
void spi_setPins(uint8_t spiNum)
{
	const uint8_t altFunc = 5; // see Figure 17. Selecting an alternate function on STM32F401xB/C and STM32F401xD/E of reference manual
	
	switch(spiNum)
	{
		case(1):	// SPI1 pins
		{
			pinAltFunc(PA5, altFunc);		//	SCLK
			pinAltFunc(PA6, altFunc);		//	SDIN
			pinAltFunc(PA7, altFunc);		//	SDOUT
			break;
		}   
		case(2):	// SPI2 pins
		{
			pinAltFunc(PB13, altFunc);	//	SCLK
			pinAltFunc(PB14, altFunc);	//	SDIN
			pinAltFunc(PB15, altFunc);	//	SDOUT
			break;
		}  
		case(3):	// SPI3 pins
		{
			pinAltFunc(PC10, altFunc);	//	SCLK
			pinAltFunc(PC11, altFunc);	//	SDIN
			pinAltFunc(PC12, altFunc);	//	SDOUT
			break;		
		}
		case(4): // SPI4 pins
		{
			pinAltFunc(PE12, altFunc);	//	SCLK
			pinAltFunc(PE13, altFunc);	//	SDIN
			pinAltFunc(PE14, altFunc);	//	SDOUT
			break;
		}  
		default: // SPI1 using alternative pins
		{
			pinAltFunc(PB3, altFunc);		//	SCLK
			pinAltFunc(PB4, altFunc);		//	SDIN
			pinAltFunc(PB5, altFunc);		//	SDOUT
			break;
		} 
	}
}
//------------------------------------------------------------------------------
SPI_TypeDef * spi_getPeripheral(uint8_t spiNum)
{
	SPI_TypeDef * SPIx;
	
	switch(spiNum)
	{
		case(1): SPIx = SPI1; break;  // SPI1
		#ifdef SPI2
		case(2): SPIx = SPI2; break;  // SPI2
		#endif
		#ifdef SPI3
		case(3): SPIx = SPI3; break;  // SPI3
		#endif
		#ifdef SPI4
		case(4): SPIx = SPI4; break;  // SPI4
		#endif
		default: SPIx = SPI1;
	}
	
	return SPIx;
}
//--------------------------TX: transmit _data-----------------------------------
void spi_write(uint8_t data)
{	
	while(!(SPIx->SR & SPI_SR_TXE));		// wait for TXE bit to set -> This will indicate that the buffer is empty
	SPIx->DR = data;										// load the data into the Data Register
	
	while(!(SPIx->SR & SPI_SR_TXE));  	// wait for TXE bit to set -> This will indicate that the buffer is empty
	while((SPIx->SR & SPI_SR_BSY));  			// wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication	
	
	//  Clear the Overrun flag by reading DR and SR
	uint8_t temp = SPI1->DR;
					temp = SPI1->SR;
}
//--------------------------RX: recieve _data------------------------------------
uint8_t spi_read(void)
{
	uint8_t data = 0;
	
	while((SPIx->SR & SPI_SR_BSY));  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
	SPIx->DR = 0;  // send dummy data
	while(!(SPIx->SR & SPI_SR_RXNE));  // Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	data = SPIx->DR;
	
	return data;
}
//------------------------------------------------------------------------------
#endif	/* SPI_C Hardware SPI */
