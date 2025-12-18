#ifndef TC72_C
#define	TC72_C
//------------------------------------------------------------------------------
#include "tc72_h.h"
//------------------------------------------------------------------------------
void tc72_init(void)
{
  pinMode(CS2, OUTPUT, PUSH_PULL);
  digitalWrite(CS2, LOW);       //CS2 = 0		//Deselect initially
	
  digitalWrite(CS2, HIGH);      //CS2 = 1
  
  spi_write(CONTROL_REG);
  spi_write(START_CONV);				//Continous conversion
  
  digitalWrite(CS2, LOW);       //CS2 = 0
  delay_ms(150);
}
//------------------------------------------------------------------------------
uint8_t tc72_read(uint8_t regName)
{
  uint8_t data;
  
  digitalWrite(CS2, HIGH);      //CS2 = 1
  
  spi_write(regName);           //Access register for reading
  data = spi_read();
  
  digitalWrite(CS2, LOW);       //CS2 = 0
  
  return data;
}

//------------------------------------------------------------------------------
float tc72_getTempr(void)
{
  uint8_t data[3]; 
    
  digitalWrite(CS2, HIGH);      //CS2 = 1
  
  spi_write(MSB_REG);           //Access MSB register for reading
  data[2] = spi_read();         // MSB Byte
  data[1] = spi_read();         // LSB Byte 
  // data[0] = SPI_read();      // CONTROL Byte
  
  digitalWrite(CS2, LOW);       //CS2 = 0
  
  return toFloat((data[2] << 8) + data[1]);
}
//------------------------------------------------------------------------------
float tc72_getTempr2(void)
{
  uint8_t data[2]; 
      
  data[1] = tc72_read(MSB_REG);         // MSB 
  data[0] = tc72_read(LSB_REG);         // LSB 
  
  return toFloat((data[1] << 8) + data[0]);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result   = tempr >> 8;          //Discard LSByte (Only holds fraction flag bits)
  uint16_t count = tempr & FRAC_FLAG;          
  
  if(count) 
  { 
    result += ((count >> 6) * 0.25);    // 2^(-2) = 0.25 (result is in multiples of 0.25 LSBit for 10-bit_ res ADC)
  }
  
  return  result;
}
//------------------------------------------------------------------------------
#endif
