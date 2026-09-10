#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include "../scheduler/rr.h"
#include "../task/task.h"

#include <stdint.h>
#include <time.h>

#ifndef SYSTEM_SETTING
#define SYSTEM_SETTING

#define SYSTEM_CORE_CLOCK 36000000
#define TIME_SLICE_TICK   10

/**
 * @brief configure the SysTick timer
 * @retval None
 * @param  None
 */
void init_the_systick();

/**
 * @brief SysTick interrupt handler
 * @retval None
 * @param  None
 */
void SysTick_Handler();

/**
 * @brief block the current task for the given number of ticks
 * @retval None
 * @param  uint32_t delay_time
 */
void task_delay(uint32_t delay_time);

#endif
