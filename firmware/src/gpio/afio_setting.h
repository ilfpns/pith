#include "stm32f1xx.h"

// Prevent redefinition
#undef AFIO_EXTICR4_EXTI13
#undef EXTI_LINE13

// AFIO sets
#define AFIO_EXTICR4_EXTI13 (0x3UL << 9)

// EXTI sets
#define EXTI_LINE13 (1UL << 13)
