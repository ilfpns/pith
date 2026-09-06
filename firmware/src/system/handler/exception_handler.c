#include "exception_handler.h"

void __attribute__((naked)) SVC_Handler() {
    __asm volatile (
        "ldr r0, =current_task   \n"
        "ldr r0, [r0]            \n"
        "ldr r0, [r0, #4]        \n"
        "ldmia r0!, {r4-r11}     \n"
        "msr psp, r0             \n"
        "movs r0, #2             \n"
        "msr control, r0         \n"
        "isb                     \n"
        "ldr lr, =0xFFFFFFFD     \n"
        "bx lr                   \n"
    );
}

void __attribute__((naked)) PendSV_Handler(void) {
    __asm volatile (
        "mrs r0, psp             \n"
        "stmdb r0!, {r4-r11}     \n"

        "ldr r1, =current_task   \n"
        "ldr r1, [r1]            \n"
        "str r0, [r1, #4]        \n"

        "ldr r1, =next_task      \n"
        "ldr r1, [r1]            \n"
        "ldr r2, =current_task   \n"
        "str r1, [r2]            \n"

        "ldr r0, [r1, #4]        \n"
        "ldmia r0!, {r4-r11}     \n"

        "msr psp, r0             \n"
        "bx lr                   \n"
    );
}
