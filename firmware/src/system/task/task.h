#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include <stdint.h>

#define STACK_SIZE     256
#define MAX_TASK_COUNT 10

typedef struct {
    char    *task_name;
    uint8_t priority;
    uint8_t state;
    uint8_t *sp;
} TCB_t;

void *stack_init(uint32_t *stack_top, void (*task_enrty)(void));

/**
 * @breif Create New task func
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

void task1();
