#include "task.h"
#include "../../system/systick/systick.h"

void task1 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BS5;
        task_delay(current_task, 200);
    }
}

void task2 (void) {
    for (;;) {
        GPIOA->BSRR = GPIO_BSRR_BR5;
        task_delay(current_task, 200);
    }
}
