#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include <stdint.h>
#include <stdio.h>

#include "../task/task.h"

typedef struct {
    uint8_t time_slice;
    TCB_t   *current_task;
    TCB_t   *next_task;
} RR_t;

void round_robin_init(void);
