#include "task.h"

void task1 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        task_delay(200);
        wdg_report_alive(WDG_ID_TASK1);
    }
}

void task2 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BR5;
        task_delay(200);
        wdg_report_alive(WDG_ID_TASK2);
        wdg_supervisor();
    }
}
