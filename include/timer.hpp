#pragma once
#include <stm32f1xx.h>

// Change System Frequency
void setSystemClock()
{
    RCC->CIR = 0x009F0000;

    // Turn HSE ON
    RCC->CR |= RCC_CR_HSEON;

    // Wait Until HSE Is Ready
    while (!(RCC->CR & RCC_CR_HSERDY))
        ;
    
    //set flash wait states to 2 wait states
    FLASH->ACR &= ~(FLASH_ACR_LATENCY);
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // Set HSE Prescaler On PLL Entry
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;
    // RCC->CFGR |= RCC_CFGR_PLLXTPRE_HSE;

    //Set HSE as PLL Source
    // RCC->CFGR &= ~RCC_CFGR_PLLSRC;
    RCC->CFGR |= RCC_CFGR_PLLSRC;

    // Set PLL Multiplier
    RCC->CFGR &= ~(RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLMULL8;

    // Turn On PLL Clock
    RCC->CR |= RCC_CR_PLLON;

    // Wait Until PLL Is Ready
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ;

    // Set System To PLL CLock
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    // RCC->CFGR = (RCC->CFGR & ~(RCC_CFGR_SW)) | RCC_CFGR_SW_HSE;

    // Clear All Interrupts
    RCC->CIR = 0x009F0000;
}

// System Clock Update
uint32_t systemClockUpdate()
{
    // Get Clock Source either HSI/HSE Oscillator or PLL
    uint32_t clock_Source = (RCC->CFGR & RCC_CFGR_SWS) >> 3;

    // Get AHB Prescaler
    uint32_t AHB_Prec = (RCC->CFGR & RCC_CFGR_HPRE) >> 4;

    // Get PLL Multiplier
    uint32_t Pll_Multiplier = ((RCC->CFGR & RCC_CFGR_PLLMULL) >> 18) + 2;

    // Get PLL Source Clock
    uint32_t PLL_Source = (RCC->CFGR & RCC_CFGR_PLLSRC) >> 16;
    

    // Get HSE Oscillator Prescaler
    uint32_t HSE_Prec = (RCC->CFGR & RCC_CFGR_PLLXTPRE) >> 17;

    // Get PLL Frequency From PLL Multipler, PLL Source Clock And HSE Prescaler
    uint32_t PLL_Freq = ((uint32_t)8000000 >> (!PLL_Source + PLL_Source * HSE_Prec)) * Pll_Multiplier;
    

    // Get SYSCLC From Clock Source, PLL Frequency and AHB Prescaler
    SystemCoreClock = ((!clock_Source) * (uint32_t)8000000 + clock_Source * PLL_Freq) >> AHB_Prec;

    return PLL_Freq;
    // serialPrint("Clock Source : %d\n", clock_Source);
    // serialPrint("AHB_Prec : %d\n", AHB_Prec);
    // serialPrint("Pll_Multiplier : %d\n", Pll_Multiplier);
    // serialPrint("PLL_Source : %d\n", PLL_Source);
    // serialPrint("HSE_Prec : %d\n", HSE_Prec);
    // serialPrint("PLL_Freq : %d\n", PLL_Freq);
    // serialPrint("SystemCoreClock : %d\n", SystemCoreClock);
}

// For store tick counts in us
static __IO uint32_t usTicks;

// SysTick_Handler function will be called every 1 us
void sysTick_Handler()
{
    if (usTicks != 0)
        usTicks--;
}

void delayInit()
{
    // Update SystemCoreClock value
    SystemCoreClockUpdate();
    // Configure the SysTick timer to overflow every 1 us
    SysTick_Config(SystemCoreClock / 1000000);
}

void delayUs(uint32_t us)
{
    // Reload us value
    usTicks = us;
    // Wait until usTick reach zero
    while (usTicks)
        ;
}

void delayMs(uint32_t ms)
{
    // Wait until ms reach zero
    while (ms--)
    {
        // Delay 1ms
        delayUs(1000);
    }
}

void ms_delay(int ms)
{
    while (ms-- > 0)
    {
        volatile int x = 500;
        while (x-- > 0)
            __asm("nop");
    }
}