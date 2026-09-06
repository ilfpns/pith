#include "task.h"

void task1 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        for(uint16_t i = 0; i < 700000; i++) {}

    }
}

void task2 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BR5;
        for(uint32_t i = 0; i < 700000; i++) {}
    }
}
