#include "console.h"
#include "tables.h"
#include "mem.h"
#include "keyboard.h"
#include "multiboot_info.h"

extern u32int end;

int main(multiboot_info_t* mb_ptr)
{
  kclear();
  kprint("hleb kernel boot\n");
  kprint("setting up tables\n");
  
  kprint("GRUB multiboot lower memory found 0x");
  kprint_hex(mb_ptr->mem_lower);
  kprint(" kb\n");
  kprint("GRUB multiboot upper memory found 0x");
  kprint_hex(mb_ptr->mem_upper);
  kprint(" kb\n");
  
  if(mb_ptr->mods_count == 0)
    kprint("No GRUB modules found.\n");
  else
  {
    kprint("Found GRUB modules.\n");
    int i;
    for(i = 0; i < mb_ptr->mods_count; i++)
      kprint("Loaded ");
      multiboot_module_t *mb_module;
      mb_module = (multiboot_module_t*)mb_ptr->mods_addr;
      kprint((char*)mb_module->cmdline);
      kprint(" at address 0x");
      kprint_hex(mb_module->addr_start);
      kput('\n');
  }
  setup_tables();
  return 0;
}
