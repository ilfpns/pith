#include "stm32f1xx.h"
#include "../clock/clock_setting.h"

#include <stdint.h>
#include <stdio.h>

int main(void) {
    set_the_clock();
    printf("clock settings succeful");

    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        for (volatile uint32_t i = 0; i < 500000; i++) {}

        GPIOA->BSRR = GPIO_BSRR_BR5;
        for (volatile uint32_t i = 0; i < 500000; i++) {}
    }
}
