#include "rr.h"

RR_t *RR;

void round_robin_init(void) {
    RR->time_slice = 10;
    RR->current_task = current_task;
    RR->next_task = &tcb_pool[(task_count + 1) % MAX_TASK_COUNT];
}
