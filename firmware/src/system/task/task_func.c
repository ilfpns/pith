#include "task.h"
#include "../systick/systick.h"
#include "../SafeSystem/IWDG/IWDG.h"

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
        supervisor_iwdg();
    }
}
