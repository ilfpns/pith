#include "stm32f1xx.h"
#include "clock_setting.h"

void set_the_clock () {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
    GPIOA->CRL |= GPIO_CRL_MODE5_0;

    GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
    GPIOC->CRH |= GPIO_CRH_CNF13_1;
    GPIOC->ODR |= GPIO_ODR_ODR13;

    return;
}
