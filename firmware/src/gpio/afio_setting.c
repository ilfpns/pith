#include "stm32f1xx.h"
#include "afio_setting.h"

void set_the_exti() {
    EXTI->IMR |= EXTI_LINE13;
    EXTI->FTSR |= EXTI_LINE13;
    EXTI->RTSR |= EXTI_LINE13;

}
