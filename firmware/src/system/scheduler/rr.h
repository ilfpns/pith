#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include <stdint.h>
#include <stdio.h>

#include "../task/task.h"

#ifndef RR_SETTING
#define RR_SETTING

/**
 * @brief initialize the round-robin scheduler
 * @retval None
 * @param  None
 */
void round_robin_init(void);

/**
 * @brief find the next task to run
 * @retval uint8_t
 * @param  uint8_t start_idx
 */
uint8_t find_next_task(uint8_t start_idx);

#endif
