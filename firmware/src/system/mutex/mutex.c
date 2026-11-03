#include "mutex.h"
#include "../../clock/clock_setting.h"
#include "../uart/uart.h"
#include <sys/cdefs.h>

void mutex_lock(mutex_lock_t *key) {
    while (1) {
        uint32_t save_register = __get_PRIMASK();

        __disable_irq();
        if (!(key->lock)) {
            key->lock = 1;
            key->owner = current_task;
            __set_PRIMASK(save_register);
            break;
        }
        __set_PRIMASK(save_register);

        char buf[32];
        snprintf(buf, sizeof(buf), "Mutex owner: %s\n", key->owner->task_name);
        usart2_send_string(buf);
    }

    return;
}

void mutex_unlock(mutex_lock_t *key) {
    uint32_t save_register = __get_PRIMASK();

    __disable_irq();
    key->lock = 0;
    volatile TCB_t *prev_owner = key->owner;
    key->owner = NULL;

    if (!(prev_owner == NULL)) {
        char buf[32];
        snprintf(buf, sizeof(buf), "Mutex owner: %s\n", prev_owner->task_name);
        usart2_send_string(buf);
    }
    __set_PRIMASK(save_register);

    return;
}
