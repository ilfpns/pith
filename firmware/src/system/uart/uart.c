#include "uart.h"
#include <stddef.h>

#define UART_RX_RING_SIZE   256U
#define UART_RX_RING_MASK   (UART_RX_RING_SIZE - 1U)

static volatile uint8_t  rx_ring[UART_RX_RING_SIZE];
static volatile uint32_t rx_head;
static volatile uint32_t rx_tail;

void set_the_usart2() {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = (19UL << 4) | 8UL;

    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
    USART2->CR1 |= USART_CR1_RXNEIE;
    NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
    return;
}

void usart2_send_char(char message) {
    while (!(USART2->SR & USART_SR_TXE)) { }
    USART2->DR = message;
    return;
}

void usart2_send_string(const char *message) {
    while (*message) {
        usart2_send_char(*message++);
    }

    return;
}

void USART2_IRQHandler(void) {
    uint32_t status = USART2->SR;

    if (status & (USART_SR_RXNE | USART_SR_ORE)) {
        uint8_t data = (uint8_t)USART2->DR;
        uint32_t next = (rx_head + 1U) & UART_RX_RING_MASK;

        if (next != rx_tail) {
            rx_ring[rx_head] = data;
            rx_head = next;
        }
    }
}

uint8_t usart2_receive_char(char *message) {
    if (rx_tail == rx_head) {
        return 0;
    }
    *message = (char)rx_ring[rx_tail];
    rx_tail = (rx_tail + 1U) & UART_RX_RING_MASK;
    return 1;
}

uint8_t usart2_receive_string(char *buffer, uint32_t size) {
    static char line[UART_RX_LINE_SIZE];
    static uint32_t length;
    char ch;

    if (buffer == NULL || size == 0) {
        return 0;
    }

    while (usart2_receive_char(&ch)) {
        uint8_t is_end = (ch == '\n' || ch == '\r');

        if (is_end && length == 0) {
            continue;
        }
        if (!is_end && length < UART_RX_LINE_SIZE - 1) {
            line[length++] = ch;
            continue;
        }

        uint32_t i = 0;
        while (i < length && i < size - 1) {
            buffer[i] = line[i];
            i++;
        }
        if (i < length) {
            usart2_send_string("Size is too small to read the whole line\n");
        }
        buffer[i] = '\0';
        length = 0;
        if (!is_end) {
            line[length++] = ch;
        }
        return 1;
    }

    return 0;
}
