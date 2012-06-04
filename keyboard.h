#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "io.h"
#include "isr.h"
#include "console.h"

#define ECHO 1

u8int init_keyboard();
u8int change_settings(u8int config);
u8int getchar();
void keyboard_irq(registers_t* regs);

#endif
