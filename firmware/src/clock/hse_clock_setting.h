#include "stm32f1xx.h"

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

void set_the_hsi_clock();
