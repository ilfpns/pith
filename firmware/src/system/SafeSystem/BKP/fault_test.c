#include "fault_test.h"

#ifdef FAULT_TEST

#include "../../task/task.h"
#include "../../uart/uart.h"
#include <string.h>

#define FAULT_CMD       "fault "
#define BAD_ADDRESS     0x60000000UL

static void flush_uart(void) {
    usart2_flush();
}

static void fault_bad_write(void) {
    usart2_send_string("Fault test 1: write to unmapped address\n");
    flush_uart();
    *(volatile uint32_t *)BAD_ADDRESS = 0xDEADBEEF;
}

static void fault_null_call(void) {
    void (* volatile null_func)(void) = (void (*)(void))0;

    usart2_send_string("Fault test 2: call function pointer 0\n");
    flush_uart();
    null_func();
}

static void fault_undefined(void) {
    usart2_send_string("Fault test 3: undefined instruction\n");
    flush_uart();
    __asm volatile ("udf #0");
}

static void fault_div_zero(void) {
    volatile int dividend = 1;
    volatile int divisor = 0;

    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
    usart2_send_string("Fault test 4: divide by zero\n");
    flush_uart();
    volatile int result = dividend / divisor;
    (void)result;
}

static void fault_unaligned(void) {
    static uint8_t buf[8];
    volatile uint32_t *odd = (volatile uint32_t *)(buf + 1);

    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
    usart2_send_string("Fault test 5: unaligned word access\n");
    flush_uart();
    volatile uint32_t value = *odd;
    (void)value;
}

void EXTI0_IRQHandler(void) {
    __asm volatile ("udf #0");
}

static void fault_in_isr(void) {
    usart2_send_string("Fault test 7: undefined instruction inside ISR\n");
    flush_uart();
    NVIC_SetPriority(EXTI0_IRQn, 2);
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_SetPendingIRQ(EXTI0_IRQn);
    for (;;) { }
}

static void plain_reset(void) {
    usart2_send_string("Fault test 8: plain reset (no fault report expected)\n");
    flush_uart();
    NVIC_SystemReset();
}

void fault_test_run(const char *line) {
    if (strncmp(line, FAULT_CMD, strlen(FAULT_CMD)) != 0) {
        return;
    }

    switch (atoi(line + strlen(FAULT_CMD))) {
    case 1:
        fault_bad_write();
        break;
    case 2:
        fault_null_call();
        break;
    case 3:
        fault_undefined();
        break;
    case 4:
        fault_div_zero();
        break;
    case 5:
        fault_unaligned();
        break;
    case 7:
        fault_in_isr();
        break;
    case 8:
        plain_reset();
        break;
    default:
        usart2_send_string("Fault test: unknown case\n");
        break;
    }
}

#endif
