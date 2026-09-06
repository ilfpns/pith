#include "rr.h"

void round_robin_init(void) {
    uint8_t current_idx = current_task - tcb_pool;
    next_task = &tcb_pool[(current_idx + 1) % task_count];
}
