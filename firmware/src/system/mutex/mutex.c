#include "mutex.h"
#include <sys/cdefs.h>

void mutex_lock(mutex_lock_t *key) {
    while (1) {
        __disable_irq();
        if (!(key->lock)) {
            key->lock = 1;
            key->owner = current_task;
            __enable_irq();

            char buf[32];
            snprintf(buf, sizeof(buf), "Mutex owner: %s", key->owner->task_name);
            usart2_send_string(buf);
        }
        __enable_irq();
    }

    return;
}

void mutex_unlock(mutex_lock_t *key) {
    __disable_irq();
    key->lock = 0;
    key->owner = NULL;
    __enable_irq();

    return;
}
