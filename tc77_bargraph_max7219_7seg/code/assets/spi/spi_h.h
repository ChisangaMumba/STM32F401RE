#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define SCLK  PA5 
#define SDIN  PA6
#define SDOUT PA7
//------------------------------------------------------------------------------
void spi_init(uint8_t spiNum);
void spi_write(uint8_t data);
uint8_t spi_read(void);
void spi_setClock(uint8_t spiNum);
void spi_setPins(uint8_t spiNum);
SPI_TypeDef * spi_getPeripheral(uint8_t spiNum);
//------------------------------------------------------------------------------
/*
	// Datasheet section 4: Pinouts and pin description
	// Table 9. Alternate function mapping
	// SPI 1
	SPI1_SCK	PA5
	SPI1_MISO	PA6
	SPI1_MOSI	PA7

	SPI1_SCK	PB3
	SPI1_MISO	PB4
	SPI1_MOSI	PB5

	// SPI 2
	SPI2_SCK	PB10
	SPI2_MISO	PC2
	SPI2_MOSI	PC3

	SPI2_SCK	PB13
	SPI2_MISO	PB14
	SPI2_MOSI	PB15

	// SPI 3
	SPI3_SCK	PC10
	SPI3_MISO	PC11
	SPI3_MOSI	PC12

	// SPI 4
	SPI4_SCK	PE2
	SPI4_MISO	PE5
	SPI4_MOSI	PE6

	SPI4_SCK	PE12
	SPI4_MISO	PE13
	SPI4_MOSI	PE14
*/
//------------------------------------------------------------------------------
#endif		/* SPI_H Hardware SPI */
