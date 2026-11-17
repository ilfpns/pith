#include <stdint.h>
#include <stdio.h>


#ifndef MUTEX_SETTING
#define MUTEX_SETTING

#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "cmsis_gcc.h"
#include "../task/task.h"

#include <stdint.h>
#include <stdio.h>

typedef struct {
    volatile TCB_t *owner;
    volatile uint8_t lock;
    uint8_t mask_irq;       /* 1: a task holding the lock masks irq below */
    int8_t irq;             /* IRQ whose ISR also uses this mutex */
} mutex_lock_t;

/* Mutex shared with an ISR: tasks mask that IRQ while they hold the lock,
   so the ISR can never spin on a lock held by a task it has preempted. */
#define MUTEX_INIT_IRQ(irqn)  { .owner = NULL, .lock = 0, .mask_irq = 1, .irq = (irqn) }

/**
 * @brief Lock the mutex (a task also masks the mutex's shared IRQ until unlock)
 * @retval None
 * @param  mutex_lock_t *key
 */
void mutex_lock(mutex_lock_t *key);

/**
 * @brief Unlock the mutex
 * @retval None
 * @param  mutex_lock_t *key
 */
void mutex_unlock(mutex_lock_t *key);

#endif
