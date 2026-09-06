#include "stm32f103xb.h"
#include "stm32f1xx.h"

#include <stdint.h>
#include <stdio.h>

#include "../task/task.h"

#ifndef RR_SETTING
#define RR_SETTING

void round_robin_init(void);

#endif
