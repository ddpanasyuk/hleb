#include "console.h"
#include "tables.h"
#include "mem.h"
#include "keyboard.h"
#include "multiboot_info.h"
#include "isr.h"
#include "system_call.h"

extern u32int end;
extern void prog_load(u32int load, u32int from);

int main(multiboot_info_t* mb_ptr)
{
  kclear();
  kprint("hleb kernel boot\n");
  kprint("setting up tables\n");
  setup_tables();
 
  kprint("GRUB multiboot lower memory found 0x");
  kprint_hex(mb_ptr->mem_lower);
  kprint(" kb\n");
  kprint("GRUB multiboot upper memory found 0x");
  kprint_hex(mb_ptr->mem_upper);
  kprint(" kb\n");
  
  create_syscall(0x80);
  
  asm volatile("sti");
  if(mb_ptr->mods_count == 0)
    kprint("No GRUB modules found.\n");
  else
  {
    kprint("Found GRUB modules.\n");
    multiboot_module_t *mb_module;
    kprint("Loaded ");
    mb_module = (multiboot_module_t*)mb_ptr->mods_addr;
    kprint((char*)mb_module->cmdline);
    kprint(" at address 0x");
    kprint_hex(mb_module->addr_start);
    kput('\n');
    
    kprint("loading driver ");
    kprint((char*)mb_module->cmdline);
    kput('\n');
    u32int *prog_ptr = (u32int*)memret(10);
    prog_load((u32int)prog_ptr, (u32int)mb_module->addr_start);
    kprint("successful return.\n");
  }
  return 0;
}
