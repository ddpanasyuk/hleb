#include "console.h"
#include "tables.h"

int main()
{
  setup_tables();
  kclear();
  kprint("hleb kernel\0");
  return 0;
}
