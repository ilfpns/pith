#include "stm32f1xx.h"

#define APB2EN_CLOCK (RCC->APB2ENR |= RCC_APB2ENR_IOPAEN)
