#pragma once

#include <stm32f1xx.h>
#include <gpio.hpp>
#include <isr.hpp>

enum INTERRUPT_TRIGGER
{
    RISING = 0b01,
    FALLING = 0b10,
    CHANGE = 0b11
};

// NVIC Interrupt Position Calculator
// (IRQn_Type)((PIN % 5) * (PIN / 5 == 0) + 23 * (PIN / 5 == 1) + 40 * (PIN >= 10));
IRQn_Type interruptPOS(uint8_t PIN)
{
    return (IRQn_Type)((PIN % 5) * (PIN / 5 == 0) + 23 * (PIN / 5 == 1) + 40 * (PIN >= 10));
}

/********************************************************************************/
/*                              Interrupt_Functions                             */
/********************************************************************************/

bool attachInterrupt(struct PORT, uint8_t, INTERRUPT_TRIGGER, void (*)());
bool detachInterrupt(uint8_t);
void clearInterrupt(uint8_t);

bool attachInterrupt(struct PORT PORTx, uint8_t PIN, INTERRUPT_TRIGGER EDGE, void (*ISR)())
{
    if ((EXTI->IMR & (1 << PIN)) || (PIN > 15)) // Check If Interrupt Already Attached
        return 0;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;                    // Alternate Function Clock Enable
    AFIO->EXTICR[PIN / 4] |= PORTx.NUM << ((PIN % 4) * 4); // Interrupt Source Select
    EXTI->RTSR |= (EDGE & 0b01) << PIN;                    // Rising Edge Trriger Select
    EXTI->FTSR |= (EDGE & 0b10) << PIN;                    // Falling Edge Trigger Select
    EXTI->IMR |= 1 << PIN;                                 // Interrupt PIN Enable
    IRQn_Type IRQn = interruptPOS(PIN);                    // Get Interrupt Position Of NVIC Vector Table
    NVIC_SetVector(IRQn, (uint32_t)ISR);                   // Map ISR To Interrupt Vector Table
    NVIC_EnableIRQ(IRQn);                                  // NVIC Interrupt Enable
    return 1;
}

bool detachInterrupt(uint8_t PIN)
{
    if ((EXTI->IMR | ~(1 << PIN)) || (PIN > 15)) //Check If Interrupt Already Detached
        return 0;
    EXTI->IMR &= ~(1 << PIN);                              // Interrupt PIN Disable
    AFIO->EXTICR[PIN / 4] &= ~(0b1111 << ((PIN % 4) * 4)); // Interrupt Source Clear
    EXTI->RTSR &= ~(1 << PIN);                             // Rising Edge Trigger Clear
    EXTI->FTSR &= ~(1 << PIN);                             // Falling Edge Trigger Clear
    return 1;
}

void clearInterrupt(uint8_t PIN)
{
    EXTI->PR |= 1 << PIN;
}