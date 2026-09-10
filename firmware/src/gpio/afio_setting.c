#include "afio_setting.h"

static uint32_t button_count;

void set_the_exti() {
    AFIO->EXTICR[3] &= ~(0xFUL << 4);
    AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC;

    EXTI->IMR |= EXTI_LINE13;
    EXTI->FTSR |= EXTI_LINE13;
    EXTI->RTSR |= EXTI_LINE13;

    NVIC->ISER[EXTI15_10_IRQn >> 5] = (1UL << (EXTI15_10_IRQn & 0x1F));

    return;
}

void EXTI15_10_IRQHandler() {
    if (EXTI->PR & EXTI_LINE13) {
        if ((GPIOC->IDR & GPIO_IDR_IDR13) != 0) {
            // This board is active-low
            button_count++;

            char buf[32];
            snprintf(buf, sizeof(buf), "Button pressed: %u\r\n", button_count);
            usart2_send_string(buf);
        }
        else {

        }
        EXTI->PR = EXTI_LINE13;
    }

    return;
}
