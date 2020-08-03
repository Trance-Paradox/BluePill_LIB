#include <stm32f1xx.h>
#include "gpio.hpp"
#include "freq.hpp"
#include "serial.hpp"
#include "interrupt.hpp"

void INT11()
{
}

int main(void)
{
    serialBegin();
    SystemCoreClockUpdate();
    pinMode(PORTC, 13, OUTPUT_PUSHPULL, OUTPUT_50MHZ);
    setSystemFreq();
    serialBegin();
    attachInterrupt(PORTA, 11, CHANGE, INT11);
    while (1)
    {
        digitalWrite(PORTC, 13, TOGGLE);
        ms_delay(1000);
        serialPrint("Hello %d %d\n", USART1->BRR, SystemCoreClock);
    }
    // serialPrint("Clock Source : %d\n", (RCC->CFGR & RCC_CFGR_SWS) >> 3);
    // serialPrint("AHB_Prec : %d\n", (RCC->CFGR & RCC_CFGR_HPRE) >> 4);
    // serialPrint("Pll_Multiplier : %d\n", ((RCC->CFGR & RCC_CFGR_PLLMULL) >> 18) + 2);
    // serialPrint("PLL_Source : %d\n", (RCC->CFGR & RCC_CFGR_PLLSRC) >> 16);
    // serialPrint("HSE_Prec : %d\n\n", (RCC->CFGR & RCC_CFGR_PLLXTPRE) >> 17);
}