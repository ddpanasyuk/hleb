#include "io.h"

void out(u16int port, u8int byte)
{
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (byte));
}

u8int in(u16int port)
{
  u8int return_value;
  asm volatile("inb %1, %0" : "=a" (return_value) : "dN" (port));
  return return_value;
}