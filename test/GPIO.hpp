#ifdef STM32F1

#include <stm32f1xx.h>

// RCC Clock Enable For Ports
#define PORTA_CLOCK_ENABLE (RCC->APB2ENR |= RCC_APB2ENR_IOPAEN)
#define PORTB_CLOCK_ENABLE (RCC->APB2ENR |= RCC_APB2ENR_IOPBEN)
#define PORTC_CLOCK_ENABLE (RCC->APB2ENR |= RCC_APB2ENR_IOPCEN)
#define PORTD_CLOCK_ENABLE (RCC->APB2ENR |= RCC_APB2ENR_IOPDEN)
#define PORTE_CLOCK_ENABLE (RCC->APB2ENR |= RCC_APB2ENR_IOPEEN)

// MODE For GPIO Operations
enum PIN_MODE : uint32_t
{
    INPUT,
    OUTPUT_10MHZ,
    OUTPUT_2MHZ,
    OUTPUT_50MHZ
};

// OUTPUT Functions
enum OUTPUT_MODE : uint32_t
{
    OUTPUT_PUSHPULL,
    OUTPUT_OPENDRAIN,
    OUTPUT_ALTERNATE_PUSHPULL,
    OUTPUT_ALTERNATE_OPENDRAIN
};

// INPUT Functions
enum INPUT_MODE : uint32_t
{
    INPUT_ANALOG,
    INPUT_FLOATING,
    INPUT_PUPD
};

// DIGITAL MODE
enum DIGITAL_MODE : uint32_t
{
    HIGH = 1,
    LOW = 1 << 15,
    TOGGLE = 1 << 15 | 1,
};

#endif

/******************************************************************************/
/*                              GPIO_Functions                                */
/******************************************************************************/

void pinMode(GPIO_TypeDef *, uint8_t, PIN_MODE, INPUT_MODE); //Initilizes Pin
void toggle(GPIO_TypeDef *, uint8_t);                        //Toggle Pin
void set(GPIO_TypeDef *, uint8_t);                           //Set Pin To HIGH
void reset(GPIO_TypeDef *, uint8_t);                         //Reset Pin To LOW
// #define reset(PORT, PIN) (PORT->BRR |= (1 << PIN))

void pinMode(GPIO_TypeDef *PORT, uint8_t PIN, PIN_MODE MODE, OUTPUT_MODE CNF)
{
    if (PIN < 8)
    {
        PORT->CRL |= (MODE << (PIN * 4));
        PORT->CRL &= ~((~MODE) << (PIN * 4));
        PORT->CRL |= (CNF << (PIN * 4 + 2));
        PORT->CRL &= ~((~CNF) << (PIN * 4 + 2));
    }
    else
    {
        PIN = PIN - 8;
        PORT->CRH |= (MODE << (PIN * 4));
        PORT->CRH &= ~((~MODE) << (PIN * 4));
        PORT->CRH |= (CNF << (PIN * 4 + 2));
        PORT->CRH &= ~((~CNF) << (PIN * 4 + 2));
    }
}

// void pinMode(struct PORT PORTx, int PIN, OUTPUT_CNF CNF, OUTPUT_SPEED MODE = OUTPUT_10MHZ)
// {
//     RCC->APB2ENR |= PORTx.RCC_APB2ENR;
//     uint64_t POS = PIN * 4, CR = (CNF << 2) | MODE;
//     PORTx.GPIOx->CRL |= (uint32_t)(CR << POS);
//     PORTx.GPIOx->CRH |= (uint32_t)((CR << POS) >> 32);
//     PORTx.GPIOx->CRL &= (uint32_t) ~(~CR << POS);
//     PORTx.GPIOx->CRH &= (uint32_t) ~((~CR << POS) >> 32);
// }

void toggle(GPIO_TypeDef *PORT, uint8_t PIN)
{
    PORT->ODR ^= (1 << PIN);
}

void set(GPIO_TypeDef *PORT, uint8_t PIN)
{
    PORT->BSRR |= (1 << PIN);
}

void reset(GPIO_TypeDef *PORT, uint8_t PIN)
{
    PORT->BRR |= (1 << PIN);
}

void digitalWrite(GPIO_TypeDef *PORT, int PIN, )
