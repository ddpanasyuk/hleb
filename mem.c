#include "mem.h"
#include "console.h"

extern u32int end;
static u32int at_memory;

void memset(u8int *addr, char val, u32int n)
{
    u8int *temp = (u8int *)addr;
    for ( ; n != 0; n--)
      *temp++ = val;
}

void *memret(u32int sz)
{
  u32int *tmp = (u32int*)at_memory;
  at_memory += sz;
  return (void*)tmp;
}

void kheapset(u32int addr)
{
  at_memory = addr;
}