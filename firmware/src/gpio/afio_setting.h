#include "stm32f1xx.h"
#include "stm32f103xb.h"

// Prevent redefinition
#undef AFIO_EXTICR4_EXTI13
#undef AFIO_EXTICR4_EXTI13_PC
#undef EXTI_LINE13

#ifndef AFIO_EXTI_SETTING
#define AFIO_EXTI_SETTING

// AFIO sets
#define AFIO_EXTICR4_EXTI13    (0x3UL << 9)
#define AFIO_EXTICR4_EXTI13_PC (0x2UL << 4)

// EXTI sets
#define EXTI_LINE13            (1UL << 13)

void EXTI15_10_IRQHandler();
void set_the_exti();

#endif
