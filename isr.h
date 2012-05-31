#ifndef _ISR_H_
#define _ISR_H_
#include "size.h"

//Again, thanks JamesM for having documentation
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
