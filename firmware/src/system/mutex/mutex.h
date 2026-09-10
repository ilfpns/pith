#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include <stdint.h>
#include <stdio.h>

#ifndef MUTEX_SETTING
#define MUTEX_SETTING

typedef struct {
    volatile uint8_t lock;
} mutex_lock_t;

void mutex_lock(mutex_lock_t *key);
void mutex_unlock(mutex_lock_t *key);

#endif
