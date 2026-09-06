#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include "../scheduler/rr.h"

#include <stdint.h>

#ifndef SYSTEM_SETTING
#define SYSTEM_SETTING

#define SYSTEM_CORE_CLOCK 72000000
#define TIME_SLICE_TICK 10

void init_the_systick();

void SysTick_Handler();

#endif
