#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include <stdint.h>
#include <stdio.h>

#include "../task/task.h"

#ifndef RR_SETTING
#define RR_SETTING

void round_robin_init(void);
uint8_t find_next_task(uint8_t start_idx);
uint8_t find_rr_task(uint8_t start_idx);

#endif
