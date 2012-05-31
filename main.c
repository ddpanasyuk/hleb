#include "console.h"
#include "tables.h"
#include "mem.h"

extern u32int end;

int main()
{
  setup_tables();
  kclear();
  kprint("hleb kernel\n\0");
  kput('\n');
  
  kprint("putting 0xCAFE into allocated memory\n\0");
  kheapset(end); //Heap init
  u32int* test = (u32int*)memret(sizeof(u32int));
  *test = 0x0000CAFE;
  kprint_hex(*test);
  kheapset(end); //Free heap memory
  
  //asm volatile("int $0x03");
  return 0;
}
