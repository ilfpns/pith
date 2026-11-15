#ifndef PITH_BKP_H
#define PITH_BKP_H

#undef FAIULT_MAGIC
#undef FAULT_NO_TASK

#include "stm32f1xx.h"
#include "stm32f103xb.h"
#include "../../../clock/clock_setting.h"
#include "../../handler/exception_handler.h"

#define FAULT_MAGIC     0xFA17U
#define FAULT_NO_TASK   0xFFFFU

/**
 * @brief Saves PC/LR/CFSR/Os_Ticks/task index to BKP DR1~DR10 then resets the system
 * @retval None
 * @param  uint32_t *frame : stacked exception frame (R0-R3, R12, LR, PC, xPSR)
 */
void hardfault_c(uint32_t *frame);

/**
 * @brief Restores the fault saved in BKP DR1~DR10, prints it over UART, then clears DR1
 * @retval None
 * @param  None
 * @note   Does nothing unless DR1 holds the fault magic. Call after set_the_usart2() and set_the_bkp_regi()
 */
void fault_report(void);

#endif
