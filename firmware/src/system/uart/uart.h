#include "stm32f1xx.h"
#include "stm32f103xb.h"

#ifndef UART_SETTING
#define UART_SETTING

// Prevent redefinition
#undef RCC_APB1ENR_USART2EN
#undef USART_CR1_UE
#undef USART_CR1_TE
#undef USART_SR_TXE

#define RCC_APB1ENR_USART2EN (0x1UL << 17)
#define USART_CR1_UE         (1UL << 13)
#define USART_CR1_TE         (1UL << 3)
#define USART_SR_TXE         (1UL << 7)

#define UART_RX_LINE_SIZE    64

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

/**
 * @brief usart2 receive interrupt handler
 * @retval None
 * @param  None
 */
void USART2_IRQHandler(void);

/**
 * @brief receive one character over usart2
 * @param  char *message
 */
uint8_t usart2_receive_char(char *message);

/**
 * @brief receive one line over usart2
 * @param  char *buffer, uint32_t size
 */
uint8_t usart2_receive_string(char *buffer, uint32_t size);

#endif
