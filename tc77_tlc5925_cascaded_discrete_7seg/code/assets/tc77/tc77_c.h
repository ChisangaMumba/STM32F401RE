#ifndef TC77_C
#define TC77_C
//------------------------------------------------------------------------------
#include "tc77_h.h"
//------------------------------------------------------------------------------
void tc77_init(void)
{
  spi_init();  
  pinMode(CS2, OUTPUT, PUSH_PULL);
  digitalWrite(CS2, HIGH);   // unselect initially

  delay_ms(300);                // Wait for the TC77 to set up
}
//------------------------------------------------------------------------------
int16_t tc77_read(void)
{   
  uint8_t data[2];  
  
  digitalWrite(CS2, LOW);    // CS2 = 0;
  
  data[1] = spi_read(); 		 // MSB
  data[0] = spi_read(); 		 // LSB
  
  digitalWrite(CS2, HIGH);   // CS2 = 1;
  
	return (data[1] << 8) + data[0];
}
//------------------------------------------------------------------------------
float tc77_getTemp(void)
{
  int16_t temp = tc77_read();

  return toFloat(temp);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result   = tempr >> 7;  // Shift right by 7 bits to get the integer part
  uint16_t count = tempr & FRAC_FLAG;          
  
  if(count) 
  {
    result += ((count >> 3) * 0.0625);  // 0.0625f is equivalent to 2^(-4) (result is in multiples of 0.0625 LSBit for 12-bit res ADC)
  }
  
  return result;
}
//------------------------------------------------------------------------------
#endif 
