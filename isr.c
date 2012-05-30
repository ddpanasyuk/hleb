//#include "isr.h"
#include "size.h"
#include "isr.h"

void isr_handler(registers_t regs)
{
    u8int num = regs.int_no & 0xFF;
    if(interrupt_func_array[num])
      interrupt_func_array[num](&regs);
    else
    {
      kprint("\npanic, unhandled interrupt\n\0");
      for(;;);
    }
}

void irq_handler(registers_t regs)
{
  u8int num = regs.int_no & 0xFF;
  if(regs.int_no >= 40)
    out(0xA0, 0x20);
  out(0x20, 0x20);
  if(interrupt_func_array[num])
    interrupt_func_array[num](&regs);
}

void add_interrupt(u8int num, void (*handler)(registers_t* regs))
{
  interrupt_func_array[num] = handler;
}

