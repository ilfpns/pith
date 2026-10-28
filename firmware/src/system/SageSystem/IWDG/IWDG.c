#include "IWDG.h"

static uint32_t volatile wdg_flag;
static uint8_t volatile wdg_fail;
static IWDG_TypeDef volatile *IWDG_struct;

uint8_t iwdg_init(void) {
    IWDG_struct->KR = 0x5555;
    IWDG_struct->PR = 4;
    IWDG_struct->RLR = 625;
    /*
     * frequency division ratio: 64
     * about 1 seconds
     */
    uint16_t timeout = 100000;
    while (IWDG_struct->SR != 0) {
        if (--timeout == 0) {
            usart2_send_string("Not arrive first IWDG signal");
            return 1;
        }
    }
    return 0;
}

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
    if (flags == WDG_ALL) {
        IWDG_struct->KR = 0xAAAA;
    }
    else if (flags != WDG_ALL) {
        wdg_fail = 1;
        return;
    }
}