#include "task.h"
#include <stdint.h>

TCB_t tcb_pool[MAX_TASK_COUNT];
uint32_t stack_mem_addr[MAX_TASK_COUNT];

TCB_t *current_task;
TCB_t *next_task;

uint8_t task_count;
uint8_t current_free_slot;
uint8_t max_priority;

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

uint32_t is_stack_ok(TCB_t *tcb) {
    return tcb->stack_mem[0] == STACK_CANARY;
}

uint8_t create_new_task(char *task_name, uint8_t priority, uint32_t stack_size, void (*stack_entry)(void)) {
    if (current_free_slot >= MAX_TASK_COUNT) {
        printf("Can't create new task \n : Max task limit (%d)\n", MAX_TASK_COUNT);
        return 1;
    }
    if (priority > 10) {
        printf("Can't create priority : (%d), smaller than 10", priority);
        return 1;
    }

    TCB_t *tcb = &tcb_pool[current_free_slot];
    tcb->task_name = task_name;
    tcb->priority = priority;

    if (current_free_slot == 0) {
        priority_verify(tcb);
    }
    current_free_slot++;
    task_count++;

    uint32_t *stack_mem = (uint32_t *)malloc(sizeof(uint32_t) * stack_size);
    if (stack_mem == NULL) {
        printf("Can't get a new stack mem\n");
        return 1;
    }
    tcb->stack_mem = stack_mem;
    stack_mem[0] = STACK_CANARY;

    uint32_t *stack_top = stack_mem + stack_size;
    tcb->sp = stack_init(stack_top, stack_entry);
    tcb->state = TASK_READY;

    if (tcb->sp == NULL) {
        printf("staack init failed");
        return 1;
    }

    return 2;
}

void priority_verify(TCB_t *tcb) {
    if (tcb->priority > max_priority) {
        max_priority = tcb->priority;
    }

    current_task = tcb;
}
