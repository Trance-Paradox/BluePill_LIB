#include <stm32f1xx.h>
#include "stdint.h"
#include <stdio.h>
#include "stdarg.h"
#include "string.h"
#include "printMsg.h"


void usart_1_enable(void)
{
  //enabling pin A9 for alternating funct. for uart/usart
   RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN; //clock to GPIO A enabled, alt.funct.en, USART1 clock enabled
	GPIOA->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1; //port A9
	GPIOA->CRH &= ~GPIO_CRH_CNF9_0; //port A9 is TX pin
	GPIOA->CRH &= ~(GPIO_CRH_MODE10_0|GPIO_CRH_MODE10_1); //port A10 is RX pin
	GPIOA->CRH |= GPIO_CRH_CNF10_0; //port A10 is RX pin
	
	//GPIOA->CRH = 0x444444B4; // A9 is alternate output, 50 MHz, push-pull - not this time short version (!)
	//clkPer/(baudRx_16bit)=72MHZ/9600 = 7500 = 0x1D4C
	/* Remove comment line for speed that you want to use*/
	//USART1->BRR = (0xEA60); //   1200 Baud
	//USART1->BRR = (0x7530); //   2400 Baud
	//USART1->BRR = (0x3A98); //   4800 Baud
	USART1->BRR = (0x1D4C); //   9600 Baud
	//USART1->BRR = (0x1388); //  14400 Baud
	//USART1->BRR = (0xEA6) ; //  19200 Baud
	//USART1->BRR = (0x9c4) ; //  28800 Baud
	//USART1->BRR = (0x753) ; //  38400 Baud
	//USART1->BRR = (0x505) ; //  56000 Baud
	//USART1->BRR = (0x4E2) ; //  57600 Baud
	//USART1->BRR = (0x271) ; // 115200 Baud
	//USART1->BRR = (0x232) ; // 128000 Baud
	//USART1->BRR = (0x119) ; // 256000 Baud
	//USART1->BRR = (0x8C)  ; // 512000 Baud
	//USART1->BRR = (0x46)  ; // 1024000 Baud
	//USART1->BRR = (0x23)  ; // 2048000 Baud
  //USART1->BRR = (0x18)  ; // 3000000 Baud (3 MHz, max speed that HTerm can get, non-standard speed)
	
	
	USART1->CR1 |= USART_CR1_TE; //transmitter enable
	USART1->CR1 |= USART_CR1_RE; //receiver enable
	USART1->CR1 |= USART_CR1_UE; //usart enable
}

void printMsg(char *msg, ...)
{
	//char buff[120]; //was 80
	va_list args;
	va_start(args,msg); 
	vsprintf(buff,msg,args);

	for(int i=0;i<strlen(buff);i++)
	{
	  USART1->DR = buff[i];
	  while(!(USART1->SR & USART_SR_TXE)); //wait for TXE, 1 = data transferred
  }
}

// int readMsg(void)
// { 
  
// 	for( len =0;len<256;len++)
// 	{
//     while(!(USART1->SR & USART_SR_RXNE));
// 	  buff[len]= USART1->DR;
//     if (buff[len]==10 || buff[len]==13) break; //if enter is pressed, providing that it is 10 or 0xA (line feed), or 13 (0xD) (carriage return) 
// 	}
// 	return len; //just returning number of entered characters, not including line feed nor carriage return (!)
// }