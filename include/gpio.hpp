#pragma once

#include <stm32f1xx.h>

struct PORT
{
	GPIO_TypeDef *GPIO;
	uint32_t RCC_APB2ENR;
	uint8_t NUM;
};

// PORT DEFINATION
// const struct PORT PORTA = {GPIOA, RCC_APB2ENR_IOPAEN};
// const struct PORT PORTB = {GPIOB, RCC_APB2ENR_IOPBEN};
// const struct PORT PORTC = {GPIOC, RCC_APB2ENR_IOPCEN};
// const struct PORT PORTD = {GPIOD, RCC_APB2ENR_IOPDEN};
// const struct PORT PORTE = {GPIOE, RCC_APB2ENR_IOPEEN};
#define PORTA ((PORT){GPIOA, RCC_APB2ENR_IOPAEN, 0}) /*!< GPIOA and its RCC */
#define PORTB ((PORT){GPIOB, RCC_APB2ENR_IOPBEN, 1}) /*!< GPIOB and its RCC */
#define PORTC ((PORT){GPIOC, RCC_APB2ENR_IOPCEN, 2}) /*!< GPIOC and its RCC */
#define PORTD ((PORT){GPIOD, RCC_APB2ENR_IOPDEN, 3}) /*!< GPIOD and its RCC */
#define PORTE ((PORT){GPIOE, RCC_APB2ENR_IOPEEN, 4}) /*!< GPIOE and its RCC */

// OUTPUT MODE
enum OUTPUT_CNF
{
	OUTPUT_PUSHPULL,
	OUTPUT_OPENDRAIN,
	OUTPUT_ALTERNATE_PUSHPULL,
	OUTPUT_ALTERNATE_OPENDRAIN
};

// OUTPUT SPEED
enum OUTPUT_SPEED
{
	OUTPUT_10MHZ = 0b01,
	OUTPUT_2MHZ,
	OUTPUT_50MHZ
};

// INPUT MODE
enum INPUT_MODE
{
	INPUT_ANALOG = 0b0000,
	INPUT_FLOATING = 0b0100,
	INPUT_PUPD = 0b1000
};

// DIGITAL STATE
enum DIGITAL_STATE
{
	LOW = 0b00,
	HIGH = 0b01,
	TOGGLE = 0b11,
};

/******************************************************************************/
/*                              GPIO_Functions                                */
/******************************************************************************/

bool pinMode(struct PORT, uint8_t, OUTPUT_CNF, OUTPUT_SPEED); // Initilizes PIN For OUTPUT
bool pinMode(struct PORT, int, INPUT_MODE);					  // Initilizes PIN For INPUT
void digitalWrite(struct PORT, int, DIGITAL_STATE);			  // Changes STATE Of OUTPUT PIN
// void toggle(GPIO_TypeDef *, int);                            		// Toggle Pin
// void set_atomic(GPIO_TypeDef *, int);                                // Set Pin To HIGH
// void reset_atomic(GPIO_TypeDef *, int);                              // Reset Pin To LOW

bool pinMode(struct PORT PORTx, uint8_t PIN, OUTPUT_CNF CNF, OUTPUT_SPEED MODE = OUTPUT_10MHZ)
{
	if (PIN >> 16)
		return 0;
	RCC->APB2ENR |= PORTx.RCC_APB2ENR | (RCC_APB2ENR_AFIOEN * (CNF / 2));
	((uint32_t *)PORTx.GPIO)[PIN >> 3] |= (CNF << 2 | MODE) << (PIN % 8) * 4;
	((uint32_t *)PORTx.GPIO)[PIN >> 3] &= ~(((CNF << 2 | MODE) ^ 0xf) << (PIN % 8) * 4);
	return 1;
}

bool pinMode(struct PORT PORTx, int PIN, INPUT_MODE CNF_MODE)
{
	if (PIN >> 16)
		return 0;
	RCC->APB2ENR |= PORTx.RCC_APB2ENR;
	((uint32_t *)PORTx.GPIO)[PIN >> 3] |= CNF_MODE << (PIN % 8) * 4;
	((uint32_t *)PORTx.GPIO)[PIN >> 3] &= ~((CNF_MODE ^ 0xf) << (PIN % 8) * 4);
	return 0;
}

void digitalWrite(struct PORT PORTx, int PIN, DIGITAL_STATE STATE)
{
	PORTx.GPIO->ODR ^= ((PORTx.GPIO->ODR & (1 << PIN)) == (uint32_t)(STATE << PIN)) ? 0 : (1 << PIN);
}

// void set_atomic(GPIO_TypeDef *GPIO, int PIN)
// {
//     GPIO->BSRR |= (1 << PIN);
// }

// void reset_atomic(GPIO_TypeDef *GPIO, int PIN)
// {
//     GPIO->BRR |= (1 << PIN);
// }

// void toggle(GPIO_TypeDef *GPIO, int PIN)
// {
//     GPIO->ODR ^= (1 << PIN);
// }
