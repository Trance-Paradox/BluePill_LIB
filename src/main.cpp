#include <stm32f1xx.h>
#include "gpio.hpp"
#include "timer.hpp"
#include "serial.hpp"

void setSystemFreq()
{
    // Turn HSE ON
    RCC->CR |= RCC_CR_HSEON;

    // Wait Until HSE Is Ready
    while (!(RCC->CR & RCC_CR_HSERDY))
        ;
    serialPrint("HSE ON\n");
    ms_delay(1000);
    // // Set HSE Prescaler On PLL Entry
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;

    // //Set PLL Source
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;

    // Set PLL Multiplier
    RCC->CFGR |= 0b1100 << 18;

    // Turn On PLL Clock
    RCC->CR |= RCC_CR_PLLON;
    serialPrint("PLL ON\n");
    ms_delay(1000);

    // Wait Until PLL Is Ready
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ;

    serialPrint("Clock ON\n");
    ms_delay(1000);
    // Set System To PLL CLock
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    ms_delay(1000);

    // Clear All Interrupts
    RCC->CIR = 0x009F0000;
}

int main(void)
{
    serialBegin();
    SystemCoreClockUpdate();
    pinMode(PORTC, 13, OUTPUT_PUSHPULL);
    setSystemFreq();
    serialBegin();
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