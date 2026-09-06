#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "task.h"

void task1 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        for(uint16_t i = 0; i < 5000; i++) {}
        GPIOA->BSRR = GPIO_BSRR_BR5;
        for(uint16_t i = 0; i < 5000; i++) {}
    }
}
