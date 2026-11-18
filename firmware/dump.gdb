set pagination off
echo \n===== WHERE =====\n
bt full
info symbol $pc
echo \n===== IPSR =====\n
p/d $xPSR & 0x1ff
echo \n===== CORE REGISTERS =====\n
info registers
echo \n===== FAULT: CFSR HFSR MMFAR BFAR =====\n
p/x *(unsigned int *)0xE000ED28
p/x *(unsigned int *)0xE000ED2C
p/x *(unsigned int *)0xE000ED34
p/x *(unsigned int *)0xE000ED38
echo \n===== MUTEX / TASK =====\n
p mutex
p current_task->task_name
