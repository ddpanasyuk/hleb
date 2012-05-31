#ifndef _MEM_H_
#define _MEM_H_
#include "size.h"

#define MAGIC 0xDEADBABE

void memset(u8int* addr, char c, u32int n);
void memcpy(u8int* addr, u8int* from, u32int n);
void *memret(u32int sz);
void kheapset(u32int addr);

#endif
