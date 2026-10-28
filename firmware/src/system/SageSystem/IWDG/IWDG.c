#include "IWDG.h"

static uint32_t volatile wdg_flag;

uint8_t init_iwdg(void) {
    IWDG->KR = 0x5555;
    IWDG->PR = 4;
    IWDG->RLR = 625;
    /*
     * frequency division ratio: 64
     * about 1 seconds
     */
    uint32_t timeout = 100000;
    while (IWDG->SR != 0) {
        if (--timeout == 0) {
            usart2_send_string("Not arrive first IWDG signal");
            return 1;
        }
    }
    IWDG->KR = 0xCCCC;
    return 0;
}

uint8_t wdg_report_alive(uint8_t id) {
    if (WDG_ID_COUNT <= id) {
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

    if (flags == WDG_ALL) {
        IWDG->KR = 0xAAAA;
    }
}