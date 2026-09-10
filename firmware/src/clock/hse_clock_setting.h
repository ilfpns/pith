#include "clock_setting.h"

#ifndef RCC_HSI_SETTING
#define RCC_HSI_SETTING

// Prevent redefinition
#undef  RCC_CFGR_SW
#undef  RCC_CFGR_SWS
#undef  RCC_CFGR_HPRE
#undef  RCC_CFGR_PPRE1
#undef  RCC_CFGR_PPRE2

#undef  RCC_CFGR_SW_HSI
#undef  RCC_CFGR_SWS_HSI
#undef  RCC_CFGR_HPRE_DIV1
#undef  RCC_CFGR_PPRE1_DIV1
#undef  RCC_CFGR_PPRE2_DIV1

#undef RCC_CR_PLLON
#undef RCC_CR_PLLRDY

#undef RCC_CFGR_PLLSRC
#undef RCC_CFGR_PLLMUL
#undef RCC_CFGR_PLLMUL9

#undef RCC_CFGR_SW_PLL
#undef RCC_CFGR_SWS_PLL

#undef FLASH_ACR_LATENCY
#undef FLASH_ACR_LATENCY_1WS

// Basic clock define
#define RCC_CFGR_SW         (0x3UL << 0)
#define RCC_CFGR_SWS        (0x3UL << 2)
#define RCC_CFGR_HPRE       (0xFUL << 4)
#define RCC_CFGR_PPRE1      (0x7UL << 8)
#define RCC_CFGR_PPRE2      (0x7UL << 11)

// HSE clock define
#define RCC_CFGR_SW_HSI     (0x0UL << 0)
#define RCC_CFGR_SWS_HSI    (0x0UL << 2)
#define RCC_CFGR_HPRE_DIV1  (0x0UL << 4)
#define RCC_CFGR_PPRE1_DIV1 (0x0UL << 8)
#define RCC_CFGR_PPRE2_DIV1 (0x0UL << 11)

#define RCC_CR_PLLON        (1UL << 24)
#define RCC_CR_PLLRDY       (1UL << 25)

#define RCC_CFGR_PLLSRC     (1UL << 16)
#define RCC_CFGR_PLLMUL     (0xFUL << 18)
#define RCC_CFGR_PLLMUL9    (0x7UL << 18)

#define RCC_CFGR_SW_PLL     (0x2UL << 0)
#define RCC_CFGR_SWS_PLL    (0x2UL << 2)

#define FLASH_ACR_LATENCY     (0x7UL << 0)
#define FLASH_ACR_LATENCY_1WS (0x1UL << 0)


/**
 * @brief configure hsi pll clock to 36mhz
 * @retval None
 * @param  None
 */
void set_the_hsi_clock();

#endif
