#ifndef PITH_FAULT_TEST_H
#define PITH_FAULT_TEST_H

#ifdef FAULT_TEST

/**
 * @brief Runs the fault injection case requested by a "fault N" UART line
 * @retval None
 * @param  const char *line : line received from UART
 * @note   Only built with FAULT_TEST. Cases that fault never return (system resets)
 */
void fault_test_run(const char *line);

#endif

#endif
