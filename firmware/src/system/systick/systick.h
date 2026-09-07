#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include "../scheduler/rr.h"

#include <stdint.h>
#include <time.h>

#ifndef SYSTEM_SETTING
#define SYSTEM_SETTING

#define SYSTEM_CORE_CLOCK 72000000
#define TIME_SLICE_TICK 10

typedef enum  {
    TASK_BLOCK   = 0,
    TASK_READY   = 1,
    TASK_RUNNING = 2,
    TASK_PREVENT = 3,
} TASK_STATE;

void init_the_systick();

void SysTick_Handler();

void task_delay(TCB_t *tcb, uint32_t delay_time);

#endif
