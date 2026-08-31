#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "afio_setting.h"

void set_the_exti() {
    AFIO->EXTICR[3] &= ~(0xFUL << 4);
    AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC;

    EXTI->IMR |= EXTI_LINE13;
    EXTI->FTSR |= EXTI_LINE13;
    EXTI->RTSR |= EXTI_LINE13;

    NVIC->ISER[EXTI15_10_IRQn >> 5] = (1UL << (EXTI15_10_IRQn & 0x1F));
}

void EXTI15_10_IRQHandler() {
    if (EXTI->PR == EXTI_LINE13) {
        if ((GPIOC->IDR & GPIO_IDR_IDR13) != 0) {
            GPIOA->BSRR = GPIO_BSRR_BS5;

            EXTI->PR &= 1UL;
        }
        else {
            GPIOA->BSRR = GPIO_BSRR_BR5;
        }
    }
}
