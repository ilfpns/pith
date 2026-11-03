#include "task.h"
#include "../systick/systick.h"
#include "../SafeSystem/IWDG/IWDG.h"
#include "../uart/uart.h"

void task1 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        task_delay(200);
        report_alive_iwdg(ID_TASK1_IWDG);
    }
}

void task2 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BR5;
        task_delay(200);
        report_alive_iwdg(ID_TASK2_IWDG);
    }
}

void task3 (void) {
    char message[256] = {0};

    for (;;) {
        if (usart2_receive_string(message, sizeof(message))) {
            usart2_send_string(message);
            usart2_send_string("\n");
        }
        task_delay(300);
        report_alive_iwdg(ID_TASK2_IWDG);
        supervisor_iwdg();
    }
}

// 출력하는 함수
