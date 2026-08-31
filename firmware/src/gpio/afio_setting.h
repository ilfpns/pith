#include "stm32f1xx.h"

// Prevent redefinition
#undef AFIO_EXTICR4_EXTI13
#undef AFIO_EXTICR4_EXTI13_PC

#undef EXTI_LINE13

// AFIO sets
#define AFIO_EXTICR4_EXTI13 (0x3UL << 9)
#define AFIO_EXTICR4_EXTI13_PC (0x2UL << 2)

// EXTI sets
#define EXTI_LINE13 (1UL << 13)

void EXTI15_10_IRQHandler();
void set_the_exti();
