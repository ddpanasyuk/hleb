#include "mem.h"

void memset(u8int *addr, char val, u32int n)
{
    u8int *temp = (u8int *)addr;
    for ( ; n != 0; n--)
      *temp++ = val;
}