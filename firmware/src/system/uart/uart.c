#include "uart.h"

void set_the_usart2() {
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->BRR = (19UL << 4) | 8UL;

    USART2->CR1 |= USART_CR1_UE | USART_CR1_TE;
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
