#include "hse_clock_setting.h"
#include "stm32f103xb.h"
#include "clock_setting.h"

void set_the_gpio_regi () {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    GPIOA->CRL &= ~(GPIO_CRL_CNF5 | GPIO_CRL_MODE5);
    GPIOA->CRL |= GPIO_CRL_MODE5_0;

    GPIOA->CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
    GPIOA->CRL |= GPIO_CRL_CNF2_1;
    GPIOA->CRL |= (GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1);

    GPIOA->CRL &= ~(GPIO_CRL_CNF3 | GPIO_CRL_MODE3);
    GPIOA->CRL |= GPIO_CRL_CNF3_0;

    GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13);
    GPIOC->CRH |= GPIO_CRH_CNF13_1;
    GPIOC->ODR |= GPIO_ODR_ODR13;

    return;
}

void set_the_hsi_clock() {
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;
    RCC->CFGR &= ~RCC_CFGR_PLLMUL;
    RCC->CFGR |= RCC_CFGR_PLLMUL9;

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY)) { }

    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_1WS;

    RCC->CFGR &= ~(RCC_CFGR_SW | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);
    RCC->CFGR |= (RCC_CFGR_PPRE1_DIV1 | RCC_CFGR_PPRE2_DIV1);

    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) { }

    return;
}

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
