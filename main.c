#include "console.h"
#include "tables.h"

int main()
{
  setup_tables();
  kclear();
  kprint("hleb kernel\n\0");
  kprint_hex(0x1245ABCD);
  
  asm volatile("int $0x03");
  return 0;
}
