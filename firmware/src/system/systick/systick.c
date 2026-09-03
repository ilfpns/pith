#include "systick.h"

SysTick_Type *SysTick_t;
volatile uint32_t Os_Ticks;

void init_the_systick() {
    SysTick_t->LOAD = (SYSTEM_CORE_CLOCK / 1000U) - 1;
    SysTick_t->VAL = 0U;
    SysTick_t->CTRL =
        SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_TICKINT_Msk   |
        SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler() {
    Os_Ticks++;
}
