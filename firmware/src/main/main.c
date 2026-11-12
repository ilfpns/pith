#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "cmsis_gcc.h"

#include "../clock/clock_setting.h"
#include "../gpio/afio_setting.h"
#include "../system/systick/systick.h"
#include "../system/task/task.h"
#include "../system/SafeSystem/IWDG/IWDG.h"
#include "../system/uart/uart.h"

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
    uint8_t create_failed = 0;
    err_state = create_new_task("LED_ON_TASK", 5, 256, task1);
    if (err_state == 1) {
        usart2_send_string("Error create new LED_ON_TASK\n");
        create_failed = 1;
    }

    err_state = create_new_task("LED_OFF_TASK", 5, 512, task2);
    if (err_state == 1) {
        usart2_send_string("Error create new LED_OFF_TASK\n");
        create_failed = 1;
    }

    err_state = create_new_task("USART_RX_TASK", 7, 1024, task3);
    if (err_state == 1) {
        usart2_send_string("Error create new USART_RX_TASK\n");
        create_failed = 1;
    }

    err_state = create_new_task("IDLE_TASK", 0, 128, idle_task);
    if (err_state == 1) {
        usart2_send_string("Error create new IDLE_TASK\n");
        create_failed = 1;
    }


    if (create_failed) {
        NVIC_SystemReset();
    }

    uint8_t err = init_iwdg();
    if (err == 1) {
        usart2_send_string("Error initiating IWDG\n");
        while (1) {
            // 인터럽트 분석 후 다시 재구동 코드
        }
    }
    __asm volatile("svc 0");

    for (;;) {}
}
