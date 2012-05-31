#include "time.h"

u32int ms_left = 0;

void timer_IRQ(registers_t* regs)
{
  if(ms_left)
    ms_left--;
}

void create_timer(u32int freq)
{
  //we want 1000 hz
  u32int divide = 1193180 / 1193;
  out(0x43, 0x36);
  out(0x40, (u8int)(divide & 0xFF));
  out(0x40, (u8int)((divide >> 8) & 0xFF));
  
  add_interrupt(IRQ0, (void*)&timer_IRQ);
}

void sleep(u32int ms)
{
  ms_left = ms;
  while(ms_left){}
}