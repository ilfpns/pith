#include "stm32f1xx.h"
#include "stm32f103xb.h"

#ifndef GPIO_SETTING
#define GPIO_SETTING

// Prevent redefinition
#undef RCC_APB2ENR_IOPAEN
#undef RCC_APB2ENR_IOPCEN
#undef RCC_APB2ENR_AFIOEN

#undef GPIO_CRL_CNF5
#undef GPIO_CRL_MODE5
#undef GPIO_CRL_MODE5_0

#undef GPIO_BSRR_BS5
#undef GPIO_BSRR_BR5

#undef GPIO_CRH_CNF13
#undef GPIO_CRH_CNF13_1
#undef GPIO_CRH_MODE13

#undef GPIO_IDR_IDR13
#undef GPIO_ODR_ODR13

#undef GPIO_CRL_CNF2
#undef GPIO_CRL_CNF2_1

#undef GPIO_CRL_MODE2
#undef GPIO_CRL_MODE2_0
#undef GPIO_CRL_MODE2_1

#undef GPIO_CRL_CNF3
#undef GPIO_CRL_CNF3_0
#undef GPIO_CRL_MODE3

#undef RCC_APB1ENR_USART2EN
#undef USART_CR1_UE
#undef USART_CR1_TE
#undef USART_SR_TXE

// Pin Clock
#define GPIO_CRL_CNF5      (0x3UL << 22)
#define GPIO_CRL_MODE5     (0x3UL << 20)
#define GPIO_CRL_MODE5_0   (0x1UL << 20)

#define GPIO_CRL_CNF2      (0x3UL << 10)
#define GPIO_CRL_CNF2_1    (0x3UL << 10)

#define GPIO_CRL_MODE2     (0x3UL << 8)
#define GPIO_CRL_MODE2_0   (0x1UL << 8)
#define GPIO_CRL_MODE2_1   (0x2UL << 8)

#define GPIO_CRL_CNF3      (0x3UL << 14)
#define GPIO_CRL_CNF3_0    (0x1UL << 14)
#define GPIO_CRL_MODE3     (0x3UL << 12)

#define GPIO_CRH_CNF13     (0x3UL << 22)
#define GPIO_CRH_CNF13_1   (0x2UL << 22)
#define GPIO_CRH_MODE13    (0x3UL << 20)

// Init peripheral register
#define RCC_APB2ENR_AFIOEN (1UL << 0)
#define RCC_APB2ENR_IOPAEN (1UL << 2)
#define RCC_APB2ENR_IOPCEN (1UL << 4)

#define RCC_APB1ENR_USART2EN (0x1UL << 17)
#define USART_CR1_UE         (1UL << 13)
#define USART_CR1_TE         (1UL << 3)
#define USART_SR_TXE         (1UL << 7)

// Bsrr configuration
#define GPIO_BSRR_BS5      (1UL << 5)
#define GPIO_BSRR_BR5      (1UL << 21)

// IDR & ODR
#define GPIO_IDR_IDR13     (1UL << 13)
#define GPIO_ODR_ODR13     (1UL << 13)

/**
 * @brief configure gpio registers
 * @retval None
 * @param  None
 */
void set_the_gpio_regi();

/**
 * @brief configure hsi pll clock to 36mhz
 * @retval None
 * @param  None
 */
void set_the_hsi_clock();

/**
 * @brief initialize usart2
 * @retval None
 * @param  None
 */
void set_the_usart2();

/**
 * @brief send one character over usart2
 * @retval None
 * @param  char message
 */
void usart2_send_char(char message);

/**
 * @brief send a string over usart2
 * @retval None
 * @param  const char *message
 */
void usart2_send_string(const char *message);

#endif
