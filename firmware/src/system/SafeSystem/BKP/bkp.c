#include "bkp.h"
#include "../../task/task.h"
#include "../../uart/uart.h"
#include <stdio.h>


void hardfault_c(uint32_t *frame) {
    uint32_t task = FAULT_NO_TASK;
    if (current_task >= tcb_pool && current_task < tcb_pool + MAX_TASK_COUNT) {
        task = (uint32_t)(current_task - tcb_pool);
    }

    uint32_t lr   = frame[5];
    uint32_t pc   = frame[6];
    uint32_t cfsr = SCB->CFSR;
    uint32_t tick = Os_Ticks;

    BKP->DR2  = pc & 0xFFFF;
    BKP->DR3  = pc >> 16;
    BKP->DR4  = lr & 0xFFFF;
    BKP->DR5  = lr >> 16;
    BKP->DR6  = cfsr & 0xFFFF;
    BKP->DR7  = cfsr >> 16;
    BKP->DR8  = tick & 0xFFFF;
    BKP->DR9  = tick >> 16;
    BKP->DR10 = task;
    BKP->DR1  = FAULT_MAGIC;

    NVIC_SystemReset();
}

void fault_report(void) {
    if (BKP->DR1 != FAULT_MAGIC) {
        return;
    }

    uint32_t task = BKP->DR10 & 0xFFFF;
    uint32_t tick = (BKP->DR8 & 0xFFFF) | (BKP->DR9 << 16);
    uint32_t cfsr = (BKP->DR6 & 0xFFFF) | (BKP->DR7 << 16);
    uint32_t lr   = (BKP->DR4 & 0xFFFF) | (BKP->DR5 << 16);
    uint32_t pc   = (BKP->DR2 & 0xFFFF) | (BKP->DR3 << 16);

    char buf[96];
    snprintf(buf, sizeof(buf), "HardFault: PC=0x%08lX LR=0x%08lX CFSR=0x%08lX\n", (unsigned long)pc, (unsigned long)lr, (unsigned long)cfsr);
    usart2_send_string(buf);

    if (task == FAULT_NO_TASK) {
        snprintf(buf, sizeof(buf), "  tick=%lu task=none\n", (unsigned long)tick);
    } else {
        snprintf(buf, sizeof(buf), "  tick=%lu task=%lu\n", (unsigned long)tick, (unsigned long)task);
    }
    usart2_send_string(buf);

    BKP->DR1 = 0;
}
