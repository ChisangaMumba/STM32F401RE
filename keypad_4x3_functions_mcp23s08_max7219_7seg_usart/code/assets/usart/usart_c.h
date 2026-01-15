#ifndef USART_C
#define USART_C
//------------------------------------------------------------------------------
#include "usart_h.h"
//------------------------------------------------------------------------------
// USART1 -> PA9  (Tx) and PA10 (Rx)
// USART2 -> PA2  (Tx) and PA3  (Rx)
// USART6 -> PA11 (Tx) and PA12 (Rx)
//------------------------------------------------------------------------------
static USART_TypeDef * USARTx;
//------------------------------------------------------------------------------	
void usart_init(uint8_t usartNum, uint32_t baudrate) 
{ 
	USARTx = usart_number(usartNum);
	IRQn_Type IRQn = usart_irq(usartNum);
	
	usart_setClock(usartNum);
	usart_setPins(usartNum);
	
	USARTx->BRR = SYSCLK_HZ / baudrate; // baud rate @ 16 MHz. 
	USARTx->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE; // Enable TX, RX and RX interrupt
	USARTx->CR1 |= USART_CR1_UE; // Enable USARTx
	
	NVIC_EnableIRQ(IRQn); // Enable USARTx interrupt in NVIC
}
//-----------------------------------------------------------------------------
void usart_setClock(uint8_t usartNum)
{ 
	switch(usartNum)
	{
		case(1): RCC->APB2ENR |= RCC_APB2ENR_USART1EN; break; // Enable USART1 clock
		case(2): RCC->APB1ENR |= RCC_APB1ENR_USART2EN; break; // Enable USART2 clock
		case(6): RCC->APB2ENR |= RCC_APB2ENR_USART6EN; break; // Enable USART6 clock
		default: RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	}
}
//-----------------------------------------------------------------------------
// Alterative Function for USART1 & USART2 is 7, USART6 is 8. See datasheet (NOT refrence manual) - Table 9: Alternate function mapping
//-----------------------------------------------------------------------------
void usart_setPins(uint8_t usartNum)
{ 	
	switch(usartNum)
	{
		//									Tx											Rx
		case(1): pinAltFunc(PA9,  0x07);  pinAltFunc(PA10, 0x07); 	break;	// Enable USART1 clock
		case(2): pinAltFunc(PA2,  0x07);  pinAltFunc(PA3,  0x07);		break;	// Enable USART2 clock
		case(6): pinAltFunc(PA11, 0x08);  pinAltFunc(PA12, 0x08);		break; 	// Enable USART6 clock
		default: pinAltFunc(PA9,  0x07);  pinAltFunc(PA10, 0x07);
	}
}
//-----------------------------------------------------------------------------
USART_TypeDef * usart_number(uint8_t usartNum)
{
	USART_TypeDef * USARTx;
	
	switch(usartNum)
	{
		case(1): USARTx = USART1; break;
		#ifdef USART2
		case(2): USARTx = USART2; break;
		#endif
		#ifdef USART3
		case(3): USARTx = USART3; break;
		#endif
		#ifdef USART4
		case(4): USARTx = USART4; break;
		#endif
		#ifdef USART5
		case(5): USARTx = USART5; break;
		#endif
		#ifdef USART6
		case(6): USARTx = USART6; break;
		#endif
		default: USARTx = USART1;
	}
	
	return USARTx;
}
//-----------------------------------------------------------------------------
IRQn_Type usart_irq(uint8_t usartNum)
{
	IRQn_Type IRQn;
	
	switch(usartNum)
	{
		case (1): IRQn = USART1_IRQn; break;
		#ifdef USART2
		case (2): IRQn = USART2_IRQn; break;
		#endif
		#ifdef USART3
		case (3): IRQn = USART3_IRQn; break;
		#endif
		#ifdef USART4
		case (4): IRQn = USART4_IRQn; break;
		#endif
		#ifdef USART5
		case (5): IRQn = USART5_IRQn; break;
		#endif
		#ifdef USART6
		case (6): IRQn = USART6_IRQn; break;
		#endif
		default : IRQn = USART1_IRQn;
	}
	
	return IRQn;
} 
//------------------------------------------------------------------------------
// Interface to the C standard I/O library. All I/O are directed to the console
//------------------------------------------------------------------------------
struct __FILE { int handle; };
FILE __stdout = { 1 };
FILE __stdin = { 0 };
FILE __stderr = { 2 };
//------------------------------------------------------------------------------
// 													Called by C library console output
//------------------------------------------------------------------------------
int fputc(int chr, FILE *f) 
{
	while(!(USARTx->SR & USART_SR_TXE));
	USARTx->DR = chr;
	
	return chr;
}
//------------------------------------------------------------------------------
int fgetc(FILE *f) 
{
	while(!(USARTx->SR & USART_SR_RXNE));
	int chr = USARTx->DR;
	
	return USARTx->DR;
}
//------------------------------------------------------------------------------
void USART1_IRQHandler(void) 
{
	if(USARTx->SR & USART_SR_RXNE) 
	{
		// Check if data is received
		uint8_t chr = getchar(); // Read received character
		
		if(is_TReceived == false)
		{			
			if(chr == 'T' || chr == 't') 
			{
				is_TReceived = true;
				printf("Feedback: start cmd '%c' received\r\n", chr);
			}		
		}
	}
}
//------------------------------------------------------------------------------
void USART2_IRQHandler(void) 
{
	if(USARTx->SR & USART_SR_RXNE) 
	{ 	
		uint8_t chr = getchar(); 
		
		if(is_TReceived == false)
		{			
			if(chr == 'T' || chr == 't') 
			{
				is_TReceived = true;
				printf("Feedback: start cmd '%c' received\r\n", chr);
			}		
		}
	}
}
//------------------------------------------------------------------------------
void USART6_IRQHandler(void) 
{
	if(USARTx->SR & USART_SR_RXNE) 
	{
		uint8_t chr = getchar(); 
		
		if(is_TReceived == false)
		{			
			if(chr == 'T' || chr == 't') 
			{
				is_TReceived = true;
				printf("Feedback: start cmd '%c' received\r\n", chr);
			}		
		}
	}
}
//------------------------------------------------------------------------------
#endif	/* USART_C */

