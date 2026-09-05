#include "task.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static TCB_t tcb_pool[MAX_TASK_COUNT];
uint32_t stack_mem_addr[MAX_TASK_COUNT];

uint8_t current_free_slot;

void *stack_init(uint32_t *stack_top, void (*task_enrty)(void)) {
    *(--stack_top) = 0x1000000;             // xPSR Thumb bit
    *(--stack_top) = (uint32_t)task_enrty;  // PC
    *(--stack_top) = 0xFFFFFFFD;            // LR   - EXC_RETURN (PSP, no FPU)
    *(--stack_top) = 0;                     // R12
    *(--stack_top) = 0;                     // R3
    *(--stack_top) = 0;                     // R2
    *(--stack_top) = 0;                     // R1
    *(--stack_top) = 0;                     // R0

    *(--stack_top) = 0;                     // R11
    *(--stack_top) = 0;                     // R10
    *(--stack_top) = 0;                     // R9
    *(--stack_top) = 0;                     // R8
    *(--stack_top) = 0;                     // R7
    *(--stack_top) = 0;                     // R6
    *(--stack_top) = 0;                     // R5
    *(--stack_top) = 0;                     // R4

    return stack_top;
}

uint8_t create_new_task(char *task_name, uint8_t priority, uint32_t stack_size, void (*stack_entry)(void)) {
    if (current_free_slot >= MAX_TASK_COUNT) {
        printf("Can't create new task \n : Max task limit (%d)\n", MAX_TASK_COUNT);
        return 1;
    }

    TCB_t *tcb = &tcb_pool[current_free_slot];

    tcb->task_name = task_name;
    tcb->priority = priority;

    uint32_t *stack_mem = (uint32_t *)malloc(sizeof(uint32_t) * stack_size);
    if (stack_mem == NULL) {
        printf("Can't get a new stack mem\n");
    }

    uint32_t *add_stack_mem_addr = &stack_mem[current_free_slot++];

    uint32_t *stack_top = stack_mem + stack_size;
    tcb->sp = stack_init(stack_top, stack_entry);

    if (tcb->sp == NULL) {
        printf("staack init failed");
        return 1;
    }

    return 2;
}
