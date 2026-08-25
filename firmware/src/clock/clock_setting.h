#include "stm32f1xx.h"

// Prevent redefinition
#undef  APB2EN_CLOCK
#undef  RCC_APB2ENR_IOPAEN

#undef GPIO_CRL_CNF5
#undef GPIO_CRL_MODE5
#undef GPIO_CRL_MODE5_0

#undef GPIO_BSRR_BS5
#undef GPIO_BSRR_BR5

// Pin Clock
#define GPIO_CRL_CNF5 (0x3UL << 22)
#define GPIO_CRL_MODE5 (0x3UL << 20)
#define GPIO_CRL_MODE5_0 (0x1UL << 20)

// Init peripheral register
#define  RCC_APB2ENR_IOPAEN (1UL << 2)

// Bsrr configuration
#define GPIO_BSRR_BS5 (1UL << 5)
#define GPIO_BSRR_BR5 (1UL << 21)

void set_the_clock() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
    GPIOA->CRL |= GPIO_CRL_MODE5_0;
}
