#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "cmsis_gcc.h"

#include "../clock/clock_setting.h"
#include "../gpio/afio_setting.h"
#include "../system/systick/systick.h"
#include "../system/task/task.h"
#include "../system/SageSystem/IWDG/IWDG.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    set_the_hsi_clock();
    set_the_usart2();
    set_the_gpio_regi();
    set_the_exti();
    if (RCC->CSR & RCC_CSR_IWDGRSTF) {
        usart2_send_string("Reset by IWDG\n");
    }
    RCC->CSR |= RCC_CSR_RMVF;

    init_the_systick();

    // init LED
    GPIOA->BSRR = GPIO_BSRR_BR5;
    uint8_t err_state;
    err_state = create_new_task("Task1", 5, 256, task1);
    if (err_state == 1) {
        printf("Error create new task1");
    }

    err_state = create_new_task("Task2", 5, 513, task2);
    if (err_state == 1) {
        printf("Error create new task2");
    }
    uint8_t err = init_iwdg();
    if (err == 1) {
        usart2_send_string("Error initiating IWDG");
        while (1) {
            // 인터럽트 분석 후 다시 재구동 코드
        }
    }
    __asm volatile("svc 0");

    for (;;) {}
}
