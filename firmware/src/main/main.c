#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "../clock/clock_setting.h"

#include <math.h>
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

        if ((GPIOC->IDR & GPIO_IDR_IDR13) == 0) {
            printf("1");
        } else {
            printf("0");
        }
    }
}
