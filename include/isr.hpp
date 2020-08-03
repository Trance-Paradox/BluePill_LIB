#pragma once

#include <stm32f1xx.h>
#include <gpio.hpp>

const void WWDG_IRQ(void (*ISR)()) /*!< Window WatchDog Interrupt                            */
{
    ISR();
}
void PVD_IRQ(void (*ISR)()) /*!< PVD through EXTI Line detection Interrupt            */
{
}
void TAMPER_IRQ(void (*ISR)()) /*!< Tamper Interrupt                                     */
{
}
void RTC_IRQ(void (*ISR)()) /*!< RTC global Interrupt                                 */
{
}
void FLASH_IRQ(void (*ISR)()) /*!< FLASH global Interrupt                               */
{
}
void RCC_IRQ(void (*ISR)()) /*!< RCC global Interrupt                                 */
{
}
void EXTI0_IRQ(void (*ISR)()) /*!< EXTI Line0 Interrupt                                 */
{
}
void EXTI1_IRQ(void (*ISR)()) /*!< EXTI Line1 Interrupt                                 */
{
}
void EXTI2_IRQ(void (*ISR)()) /*!< EXTI Line2 Interrupt                                 */
{
}
void EXTI3_IRQ(void (*ISR)()) /*!< EXTI Line3 Interrupt                                 */
{
}
void EXTI4_IRQ(void (*ISR)()) /*!< EXTI Line4 Interrupt                                 */
{
}
void DMA1_Channel1_IRQ(void (*ISR)()) /*!< DMA1 Channel 1 global Interrupt                      */
{
}
void DMA1_Channel2_IRQ(void (*ISR)()) /*!< DMA1 Channel 2 global Interrupt                      */
{
}
void DMA1_Channel3_IRQ(void (*ISR)()) /*!< DMA1 Channel 3 global Interrupt                      */
{
}
void DMA1_Channel4_IRQ(void (*ISR)()) /*!< DMA1 Channel 4 global Interrupt                      */
{
}
void DMA1_Channel5_IRQ(void (*ISR)()) /*!< DMA1 Channel 5 global Interrupt                      */
{
}
void DMA1_Channel6_IRQ(void (*ISR)()) /*!< DMA1 Channel 6 global Interrupt                      */
{
}
void DMA1_Channel7_IRQ(void (*ISR)()) /*!< DMA1 Channel 7 global Interrupt                      */
{
}
void ADC1_2_IRQ(void (*ISR)()) /*!< ADC1 and ADC2 global Interrupt                       */
{
}
void USB_HP_CAN1_TX_IRQ(void (*ISR)()) /*!< USB Device High Priority or CAN1 TX Interrupts       */
{
}
void USB_LP_CAN1_RX0_IRQ(void (*ISR)()) /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
{
}
void CAN1_RX1_IRQ(void (*ISR)()) /*!< CAN1 RX1 Interrupt                                   */
{
}
void CAN1_SCE_IRQ(void (*ISR)()) /*!< CAN1 SCE Interrupt                                   */
{
}
void EXTI9_5_IRQ(void (*ISR)()) /*!< External Line[9:5] Interrupts                        */
{
}
void TIM1_BRK_IRQ(void (*ISR)()) /*!< TIM1 Break Interrupt                                 */
{
}
void TIM1_UP_IRQ(void (*ISR)()) /*!< TIM1 Update Interrupt                                */
{
}
void TIM1_TRG_COM_IRQ(void (*ISR)()) /*!< TIM1 Trigger and Commutation Interrupt               */
{
}
void TIM1_CC_IRQ(void (*ISR)()) /*!< TIM1 Capture Compare Interrupt                       */
{
}
void TIM2_IRQ(void (*ISR)()) /*!< TIM2 global Interrupt                                */
{
}
void TIM3_IRQ(void (*ISR)()) /*!< TIM3 global Interrupt                                */
{
}
void TIM4_IRQ(void (*ISR)()) /*!< TIM4 global Interrupt                                */
{
}
void I2C1_EV_IRQ(void (*ISR)()) /*!< I2C1 Event Interrupt                                 */
{
}
void I2C1_ER_IRQ(void (*ISR)()) /*!< I2C1 Error Interrupt                                 */
{
}
void I2C2_EV_IRQ(void (*ISR)()) /*!< I2C2 Event Interrupt                                 */
{
}
void I2C2_ER_IRQ(void (*ISR)()) /*!< I2C2 Error Interrupt                                 */
{
}
void SPI1_IRQ(void (*ISR)()) /*!< SPI1 global Interrupt                                */
{
}
void SPI2_IRQ(void (*ISR)()) /*!< SPI2 global Interrupt                                */
{
}
void USART1_IRQ(void (*ISR)()) /*!< USART1 global Interrupt                              */
{
}
void USART2_IRQ(void (*ISR)()) /*!< USART2 global Interrupt                              */
{
}
void USART3_IRQ(void (*ISR)()) /*!< USART3 global Interrupt                              */
{
}
void EXTI15_10_IRQ(void (*ISR)()) /*!< External Line[15:10] Interrupts                      */
{
}
void RTC_Alarm_IRQ(void (*ISR)()) /*!< RTC Alarm through EXTI Line Interrupt                */
{
}
void USBWakeUp_IRQ(void (*ISR)()) /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */
{
}

struct
{
    const void (*WWDG_ISR)(void (*)()) = WWDG_IRQ;
    void(*ISR)();
}const IRQ_Handler;