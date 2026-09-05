#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include "../clock/clock_setting.h"
#include "../clock/hse_clock_setting.h"
#include "../gpio/afio_setting.h"
#include "../system/systick/systick.h"
#include "../system/task/task.h"

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

    uint8_t err_state = create_new_task("Task1", 5, 256, task1);
    if (err_state) {

    }

    for (;;) {}
}
