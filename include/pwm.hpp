#pragma once

#include <stm32f1xx.h>
#include <gpio.hpp>

struct PIN
{
    /* data */
};


void PWM();

void PWM()
{
    pinMode(PORTB, 1, OUTPUT_ALTERNATE_PUSHPULL, OUTPUT_50MHZ);

    RCC->APB2ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->CR1 &= ~(TIM_CR1_CMS | TIM_CR1_DIR);
    TIM3->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;

    TIM3->PSC = 8;
    TIM3->ARR = 1000;
    TIM3->CCR4 = 500;

    TIM3->CCMR2 |= TIM_CCMR2_OC4M | TIM_CCMR2_OC4PE;
    // TIM3->CR1 |= TIM_CR1_ARPE;
    TIM3->CCER |= TIM_CCER_CC4E | TIM_CCER_CC4P;
    TIM3->BDTR |= TIM_BDTR_MOE;
    TIM3->EGR |= TIM_EGR_UG;
}