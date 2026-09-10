#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "cmsis_gcc.h"

#include "../task/task.h"
#include "../../clock/clock_setting.h"


#include <stdint.h>
#include <stdio.h>

#ifndef MUTEX_SETTING
#define MUTEX_SETTING

typedef struct {
    volatile TCB_t *owner;
    volatile uint8_t lock;
} mutex_lock_t;

void mutex_lock(mutex_lock_t *key);
void mutex_unlock(mutex_lock_t *key);

#endif
