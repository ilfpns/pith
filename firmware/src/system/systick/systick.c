#include "systick.h"

volatile uint32_t Os_Ticks;

void init_the_systick() {
    SysTick->LOAD = (SYSTEM_CORE_CLOCK / 1000U) - 1;
    SysTick->VAL = 0U;
    SysTick->CTRL =
        SysTick_CTRL_CLKSOURCE_Msk |
        SysTick_CTRL_TICKINT_Msk   |
        SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler() {
    Os_Ticks++;
}
