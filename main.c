#include "console.h"
#include "tables.h"
#include "mem.h"
#include "keyboard.h"

extern u32int end;

int main()
{
  kclear();
  kprint("hleb kernel boot\n\0");
  kprint("setting up tables\n\0");
  setup_tables();
  create_timer(0);
  asm volatile("sti");
  int i;
  for(i = 0; i < 100; i++)
  {
    kprint_hex(i);
    kput('\n');
    sleep(1000);
  }
  return 0;
}
