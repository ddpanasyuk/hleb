#ifndef _SYSTEM_CALL_H_
#define _SYSTEM_CALL_H_
#include "isr.h"

void create_syscall(u8int num);
void handle_syscall(registers_t* regs);

#endif
