#include "stm32f1xx.h"

// Prevent redefinition
#undef  RCC_APB2ENR_IOPAEN
#undef  RCC_APB2ENR_IOPCEN

#undef GPIO_CRL_CNF5
#undef GPIO_CRL_MODE5
#undef GPIO_CRL_MODE5_0

#undef GPIO_BSRR_BS5
#undef GPIO_BSRR_BR5

#undef GPIO_CRH_CNF13
#undef GPIO_CRH_CNF13_1
#undef GPIO_CRH_MODE13

#undef GPIO_IDR_IDR13
#undef GPIO_ODR_ODR13

// Pin Clock
#define GPIO_CRL_CNF5 (0x3UL << 22)
#define GPIO_CRL_MODE5 (0x3UL << 20)
#define GPIO_CRL_MODE5_0 (0x1UL << 20)

#define GPIO_CRH_CNF13 (0x3UL << 22)
#define GPIO_CRH_CNF13_1 (0x2UL << 22)
#define GPIO_CRH_MODE13 (0x3UL << 20)

// Init peripheral register
#define  RCC_APB2ENR_IOPAEN (1UL << 2)
#define  RCC_APB2ENR_IOPCEN (1UL << 4)

// Bsrr configuration
#define GPIO_BSRR_BS5 (1UL << 5)
#define GPIO_BSRR_BR5 (1UL << 21)

// IDR & ODR
#define GPIO_IDR_IDR13 (1UL << 13)
#define GPIO_ODR_ODR13 (1UL << 13)

void set_the_clock();
