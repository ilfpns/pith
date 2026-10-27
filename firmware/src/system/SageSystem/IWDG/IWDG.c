#include "IWDG.h"

static uint32_t volatile wdg_flag;
static uint8_t volatile wdg_fail;

uint8_t wdg_report_alive(uint8_t id) {
    if (WDG_ID_COUNT < id) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Cannot enter id: %d", id);
        usart2_send_string(buf);
        return 1;
    }
    __disable_irq();
    wdg_flag |= (1U << id);
    __enable_irq();

    return 0;
}

void wdg_supervisor(void) {
    uint32_t flags;

    __disable_irq();
    flags = wdg_flag;
    wdg_flag = 0;
    __enable_irq();

    if (wdg_fail) { // 다음 처리 함수 호출
        return;
    }
    if (flags != WDG_ALL) {
        wdg_fail = 1;
        return;
    }
}