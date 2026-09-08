#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "cmsis_gcc.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../gpio/afio_setting.h"
#include "../../clock/clock_setting.h"

#ifndef TASK_HEADER
#define TASK_HEADER

#define STACK_SIZE     256
#define MAX_TASK_COUNT 10
#define STACK_CANARY 0xDEADBEEF

typedef enum  {
    TASK_READY   = 0,
    TASK_RUNNING = 1,
    TASK_BLOCK   = 2,
    TASK_PREVENT = 3,
} TASK_STATE;

typedef struct {
    char     *task_name;
    uint32_t *sp;
    uint32_t *stack_mem;
    uint32_t wake_ticks;
    uint8_t  priority;
    uint8_t  state; // Do not use yet
} TCB_t;

extern TCB_t tcb_pool[MAX_TASK_COUNT];
extern TCB_t *current_task;
extern TCB_t *next_task;
extern uint8_t task_count;
extern volatile uint32_t Os_Ticks;

/**
 * @brief init the stack mem place
 * @retval none
 */
void *stack_init(uint32_t *stack_top, void (*task_enrty)(void));

/**
 * @brief Create New task func
 * @retval
 *  - 1 : Error
 *  - 2 : Succes to create new task
 *
 *
 * @param
 * - task_name  : Task name
 * - priority   : Task priority
 * - stack_size : Size of the stack used by the task
 * - stack_entry: Entry function of the task
 */
uint8_t create_new_task(char *task_name, uint8_t priority, uint32_t stack_size, void (*stack_entry)(void));

uint32_t is_stack_ok(TCB_t *tcb);

void priority_verify(TCB_t *tcb);

// task function prototype
void task1(void);
void task2(void);

#endif
