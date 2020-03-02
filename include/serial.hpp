#pragma once

#include <stm32f1xx.h>
#include <stdint.h>
#include "string.h"
#include "stdio.h"
#include <stdarg.h>
#include "timer.hpp"

void serialBegin()
{
    USART1->CR1 &= ~(USART_CR1_TE | USART_CR1_UE);
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN;
    GPIOA->CRH |= GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    systemClockUpdate();
    USART1->BRR = SystemCoreClock / 9600;
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_UE;
}

void serialPrint(const char *msg, ...)
{
    char buff[120];
    va_list args;
    va_start(args, msg);
    vsprintf(buff, msg, args);

    for (uint32_t i = 0; i < strlen(buff); i++)
    {
        USART1->DR = buff[i];
        while (!(USART1->SR & USART_SR_TXE))
            ;
    }
}
