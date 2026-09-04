#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include <stdint.h>

#define SYSTEM_CORE_CLOCK 72000000

void init_the_systick();

void SysTick_Handler();
