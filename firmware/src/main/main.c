#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include "../clock/clock_setting.h"
#include "../gpio/afio_setting.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    set_the_clock();
    printf("clock settings succeful");

    GPIOA->BSRR = GPIO_BSRR_BR5;

    for (;;) {}
}
