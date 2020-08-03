#pragma once

#include <stm32f1xx.h>

void timer(TIM_TypeDef *);

void timer(TIM_TypeDef *TIMx)
{
    TIMx->PSC;
    TIMx->ARR;
    TIMx->CR1;
}