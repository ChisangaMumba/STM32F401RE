#ifndef USART2_C
#define USART2_C
//------------------------------------------------------------------------------
#include "usart2_h.h"
//------------------------------------------------------------------------------
// USART1 -> PA9  (Tx) and PA10 (Rx)
// USART2 -> PA2  (Tx) and PA3  (Rx) *
// USART6 -> PA11 (Tx) and PA12 (Rx)
//------------------------------------------------------------------------------	
void usart2_init(uint32_t baudrate) 
{
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; // Enable USART2 clock
	
	// Set PA2 (USART2_TX) and PA3 (USART2_RX) to alternate function mode
	pinAltFunc(PA2, 0x07);	// Alterative Function for USART2 & USART1 is 7, USART6 is 8. See datasheet (NOT refrence manual) - Table 9: Alternate function mapping
	pinAltFunc(PA3, 0x07);
	
	USART2->BRR = SYSCLK_HZ / baudrate; // baud rate @ 16 MHz. 
	USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE; // Enable TX, RX and RX interrupt
	USART2->CR1 |= USART_CR1_UE; // Enable USART2
	
	NVIC_EnableIRQ(USART2_IRQn); // Enable USART2 interrupt in NVIC
}
//------------------------------------------------------------------------------
uint8_t usart2_write(uint8_t ch) 
{ 
	while(!(USART2->SR & 0x0080)); //wait until TX buffer empty 
	USART2->DR = (ch & 0xFF); 
	
	return ch; 
} 
//------------------------------------------------------------------------------
uint8_t usart2_read(void) 
{ 
	while(!(USART2->SR & 0x0020)); //wait until char arrives 
	
	return USART2->DR; 
}
//------------------------------------------------------------------------------
// Interface to the C standard I/O library. All I/O are directed to the console, which is USART2
struct __FILE { int handle; };
FILE __stdout = { 1 };
FILE __stdin = { 0 };
//------------------------------------------------------------------------------
// 													Called by C library console output
//------------------------------------------------------------------------------
int fputc(int c, FILE *f) 
{
	while(!(USART2->SR & USART_SR_TXE));
	USART2->DR = c;
	
	return c;
}
//------------------------------------------------------------------------------
int fgetc(FILE *f) 
{
	while (!(USART2->SR & USART_SR_RXNE));
	
	return USART2->DR;
}
//------------------------------------------------------------------------------
void USART2_IRQHandler(void) 
{
	if(USART2->SR & USART_SR_RXNE) 
	{ 	
		// Check if data is received
		uint8_t c = getchar(); // Read received character
		
		if(is_TReceived == false)
		{			
			
			if(c == 'T' || c == 't') 
			{
				is_TReceived = true;
				printf("Feedback: start cmd '%c' received\r\n",c);
			}		
		}
	}
}
//------------------------------------------------------------------------------
#endif	/* USART_C */

