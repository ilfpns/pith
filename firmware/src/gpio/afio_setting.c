#include "afio_setting.h"
#include "../system/mutex/mutex.h"

mutex_lock_t mutex;

static uint32_t button_count;
static uint32_t unbutton_count;

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
            mutex_lock(&mutex);
            // This board is active-low
            button_count++;

            char buf[32];
            snprintf(buf, sizeof(buf), "Button pressed: %u\r\n", button_count);
            usart2_send_string(buf);

            mutex_unlock(&mutex);
        }
        else {
            mutex_lock(&mutex);
            unbutton_count++;

            char buf[32];
            snprintf(buf, sizeof(buf), "Button unpressed: %u\r\n", unbutton_count);
            usart2_send_string(buf);
            mutex_unlock(&mutex);
        }
        EXTI->PR = EXTI_LINE13;
    }

    return;
}
