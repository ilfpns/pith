#include "stm32f1xx.h"

// Prevent redefinition
#undef AFIO_EXTICR4_EXTI13

// AFIO sets
#define AFIO_EXTICR4_EXTI13 (0x3UL << 9)
