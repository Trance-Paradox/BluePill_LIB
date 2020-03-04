#include <stm32f1xx.h>
#include "gpio.hpp"
#include "timer.hpp"
#include "serial.hpp"

void setSystemFreq()
{
	RCC->CIR = 0x009F0000;

    // Turn HSE ON
    RCC->CR |= RCC_CR_HSEON;

    // Wait Until HSE Is Ready
    while (!(RCC->CR & RCC_CR_HSERDY))
        ;
    serialPrint("HSE ON\n");

    //set HSE as system clock
    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_SW)) | RCC_CFGR_SW_HSE;

    //AHB prescaler
    RCC->CFGR &= ~(RCC_CFGR_HPRE); //remove old prescaler
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1; //set AHB prescaler = 1.
    //set ADC prescaler = 8
    RCC->CFGR &= ~(RCC_CFGR_ADCPRE);
    RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8;
    //set APB1 prescaler
    RCC->CFGR &= ~(RCC_CFGR_PPRE1);
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    //set APB2 prescaler
    RCC->CFGR &= ~(RCC_CFGR_PPRE2);
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

    //set flash wait states to 2 wait states
    FLASH->ACR &= ~(FLASH_ACR_LATENCY);
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    //Set PLL Multiplier
    //RCC->CFGR |= 0b1100 << 18;
    //at HSE=8MHz, 8*9 = 72MHz.
    RCC->CFGR &= ~(RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLMULL9;

    // //Set HSE as PLL Source. bit set -> HSE, bit unser -> HSI
    RCC->CFGR |= RCC_CFGR_PLLSRC;

    // Set HSE Prescaler On PLL Entry
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;
    RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE; //no HSE prescaler before PLL entry


    // Turn On PLL Clock
    RCC->CR |= RCC_CR_PLLON;
    serialPrint("wait for PLL ON\n");
    //ms_delay(1000);

    // Wait Until PLL Is Ready
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ;
    serialPrint("PLL rdy\n");

    //serialPrint("Clock ON\n");
    //ms_delay(1000);
    // Set System To PLL CLock
    RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_SW)) | RCC_CFGR_SW_PLL;
    serialPrint("switched to PLL clock\n");


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
