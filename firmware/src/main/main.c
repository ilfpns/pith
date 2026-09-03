#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include "../clock/clock_setting.h"
#include "../clock/hse_clock_setting.h"
#include "../gpio/afio_setting.h"
#include "../system/systick/systick.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    set_the_hsi_clock();
    set_the_gpio_regi();
    set_the_exti();

    init_the_systick();

    // init LED
    GPIOA->BSRR = GPIO_BSRR_BR5;

    for (;;) {}
}
