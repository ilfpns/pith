#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "cmsis_gcc.h"
#include "../task/task.h"

#ifndef HANDLER_SETTING
#define HANDLER_SETTING

void __attribute__((naked)) SVC_Handler();

#endif
