#include "bkp.h"

void HardFault_Handler(void) {
    BKP->DR2 = pc & 0xFFFF;
    BKP->DR3 = pc >> 16;


    NVIC_SystemReset();
}

