#ifndef PITH_IWDG_H
#define PITH_IWDG_H

#include <stdio.h>
#include <stdint.h>
#include "cmsis_gcc.h"

enum {
    ID_TASK1_IWDG,
    ID_TASK2_IWDG,
    ID_COUNT_IWDG,
};
#define ALL_IWDG ((1u << ID_COUNT_IWDG) - 1u)

/**
 * @brief init iwdg system
 * @param None
 * @return
 *  - 1 : Error
 *  - 0 : Success
 */
uint8_t init_iwdg(void);

/**
 * @brief Check the id flag
 * @param id
 * @return
 *  - 1 : Error
 *  - 0 : Success
 */
uint8_t report_alive_iwdg(uint8_t id);

/**
 * @brief Check the flag error
 * @param None
 * @return None
 */
void supervisor_iwdg(void);

#endif //PITH_IWDG_H
