#ifndef PITH_IWDG_H
#define PITH_IWDG_H

#include <stdio.h>
#include <stdint.h>
#include "cmsis_gcc.h"
#include "../../../clock/clock_setting.h"

enum {
    WDG_ID_SENSOR,
    WDG_ID_COMM,
    WDG_ID_CTRL,
    WDG_ID_COUNT,
};
#define WDG_ALL ((1u << WDG_ID_COUNT) - 1u)

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
uint8_t wdg_report_alive(uint8_t id);

/**
 * @brief Check the flag error
 * @param None
 * @return None
 */
void wdg_supervisor(void);

#endif //PITH_IWDG_H
