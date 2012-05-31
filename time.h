#ifndef _TIME_H_
#define _TIME_H_

#include "isr.h"
#include "io.h"
#include "console.h"

void sleep(u32int ms);
void create_timer(u32int freq);
void timer_IRQ(registers_t* regs);

#endif
