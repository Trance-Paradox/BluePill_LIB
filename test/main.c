/*********************************************
 USART1 TX on STM32 is at pin A9, RX is at pin
 A10. Use pinout, or CubeMX to find those two
 pins. 
==========STM32===========FTDI================
           GND------------GND pin
   pin A9  TX-------------RX  pin
   pin A10 RX-------------TX  pin
 *********************************************/

#include <stm32f1xx.h>
#include "printMsg.h"
#include "timer.hpp"

int len=0;
char buff[256];

void delay(long cycles)
{
  while(cycles >0)
  cycles--; // 'wasted clock cycles', not exact time
}



int main()
{
	usart_1_enable();
	printMsg("Here is message %d 0x%X \n", 65, 65);
			
	while(1)
	{
	
    // readMsg();
	printMsg("Here is message %d 0x%X \n", 65, 65);
    // //this part just send back to the HTerm console - the same text as received		
	// 	for (int i=0;i<len+1;i++)
	//   {
	//     USART1->DR = buff[i];
	//     while(!(USART1->SR & USART_SR_TXE)); //TXE becomes true (1) when the content of DR (data register) goes into shift register
	//   }
	}
}