#include "IWDG.h"

#include "../../task/task.h"
#include "../../../clock/clock_setting.h"
#include "../../uart/uart.h"

#define KEY_UNLOCK_IWDG        0x5555
#define KEY_START_IWDG         0xCCCC
#define KEY_KICK_IWDG          0xAAAA

#define PRESCALER_DIV64_IWDG   4
#define RELOAD_IWDG            625
#define TIMEOUT_COUNT_IWDG     100000
#define STANDARD_LINE_IWDG     500
// Supervisor's IWDG deadline

static uint32_t last_tick_iwdg[ID_COUNT_IWDG];

uint8_t init_iwdg(void) {
    RCC->CSR |= RCC_CSR_LSION;
    uint32_t lsi_timeout = TIMEOUT_COUNT_IWDG;
    while (!(RCC->CSR & RCC_CSR_LSIRDY)) {
        if (--lsi_timeout == 0) {
            usart2_send_string("LSI not ready\n");
            return 1;
        }
    }

    IWDG->KR = KEY_START_IWDG;
    IWDG->KR = KEY_UNLOCK_IWDG;
    IWDG->PR = PRESCALER_DIV64_IWDG;
    IWDG->RLR = RELOAD_IWDG;

    DBGMCU->CR |= DBGMCU_CR_DBG_IWDG_STOP;

    uint32_t timeout = TIMEOUT_COUNT_IWDG;
    while (IWDG->SR != 0) {
        if (--timeout == 0) {
            char buf[64];
            snprintf(buf, sizeof(buf), "IWDG SR=0x%lX CSR=0x%lX\n",
                     (unsigned long)IWDG->SR, (unsigned long)RCC->CSR);
            usart2_send_string(buf);
            usart2_send_string("Not arrive first IWDG signal\n");
            return 1;
        }
    }
    IWDG->KR = KEY_KICK_IWDG;
    return 0;
}

uint8_t report_alive_iwdg(uint8_t id) {
    if (ID_COUNT_IWDG <= id) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Cannot enter id: %d\n", id);
        usart2_send_string(buf);
        return 1;
    }
    last_tick_iwdg[id] = Os_Ticks;

    return 0;
}

void supervisor_iwdg(void) {
    for (int i = 0; i < ID_COUNT_IWDG; i++) {
        if ((Os_Ticks - last_tick_iwdg[i]) > STANDARD_LINE_IWDG) {
            return;
        }
    }
    IWDG->KR = KEY_KICK_IWDG;
}
