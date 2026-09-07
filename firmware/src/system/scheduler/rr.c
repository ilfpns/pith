#include "rr.h"

void round_robin_init(void) {
    uint8_t current_idx = current_task - tcb_pool;

    if ((tcb_pool[current_idx].state) == TASK_RUNNING) {
        if ((is_stack_ok(current_task))) {
            current_task->state = TASK_READY;
        }
        else {
            current_task->state = TASK_PREVENT;
        }
    }

    uint8_t next_idx = find_ready_task(current_idx);
    next_task = &tcb_pool[next_idx];
    next_task->state = TASK_RUNNING;
}

static uint8_t find_ready_task(uint8_t start_idx) {
    for (uint8_t offset = 1; offset <= task_count; offset++) {
        uint8_t idx = (start_idx + offset) % task_count;

        if (tcb_pool[idx].state == TASK_READY) {
            return idx;
        }

        if (tcb_pool[idx].state == TASK_BLOCK && Os_Ticks >= tcb_pool[idx].wake_ticks) {
            return idx;
        }
    }

    return start_idx;
}
