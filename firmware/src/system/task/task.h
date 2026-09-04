#include "stm32f103xb.h"
#include "stm32f1xx.h"

#define STACK_SIZE 256

typedef struct {
    char    task_name[20];
    uint8_t priority;
    uint8_t state;
    uint8_t *sp;
} TCB_t;

void *stack_init(uint32_t *stack_top, void (*task_enrty)(void));
