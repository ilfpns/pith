#include "IWDG.h"
#include "../../../clock/clock_setting.h"

#define KEY_UNLOCK_IWDG        0x5555
#define KEY_START_IWDG         0xCCCC
#define KEY_KICK_IWDG          0xAAAA
/* prescaler 4 : divide by 64, reload 625 : about 1 second at 40kHz LSI */
#define PRESCALER_DIV64_IWDG   4
#define RELOAD_IWDG            625
#define TIMEOUT_COUNT_IWDG     100000

static uint32_t volatile flag_iwdg;

uint8_t init_iwdg(void) {
    IWDG->KR = KEY_UNLOCK_IWDG;
    IWDG->PR = PRESCALER_DIV64_IWDG;
    IWDG->RLR = RELOAD_IWDG;

    DBGMCU->CR |= DBGMCU_CR_DBG_IWDG_STOP;

    uint32_t timeout = TIMEOUT_COUNT_IWDG;
    while (IWDG->SR != 0) {
        if (--timeout == 0) {
            usart2_send_string("Not arrive first IWDG signal\n");
            return 1;
        }
    }
    IWDG->KR = KEY_START_IWDG;
    return 0;
}

uint8_t report_alive_iwdg(uint8_t id) {
    if (ID_COUNT_IWDG <= id) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Cannot enter id: %d\n", id);
        usart2_send_string(buf);
        return 1;
    }
    uint32_t save_register = __get_PRIMASK();
    __disable_irq();
    flag_iwdg |= (1U << id);
    __set_PRIMASK(save_register);

    return 0;
}

void supervisor_iwdg(void) {
    uint32_t flags;
    uint32_t save_register = __get_PRIMASK();

    __disable_irq();
    flags = flag_iwdg;
    flag_iwdg = 0;
    __set_PRIMASK(save_register);

    if (flags == ALL_IWDG) {
        IWDG->KR = KEY_KICK_IWDG;
    }
}
