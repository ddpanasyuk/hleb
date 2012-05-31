#ifndef _ISR_H_
#define _ISR_H_
#include "size.h"

//Again, thanks JamesM for having documentation
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

struct registers
{
    u32int ds;                  
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; 
    u32int int_no, err_code;  
    u32int eip, cs, eflags, useresp, ss; 
};

typedef struct registers registers_t;

void (*interrupt_func_array[256])(registers_t* regs);
void add_interrupt(u8int num, void (*handler)(registers_t* regs));

#endif
