#include "tables.h"

extern void gdt_flush(u32int addr);
extern void idt_flush(u32int addr);
extern void *ISR_MACRO_LOC;

gdt_struct_t gdt_entry_array[4];
gdtptr_struct_t gdt_ptr;
tss_struct_t tss_entry;

idt_struct_t idt_entry_array[256];
idtptr_struct_t idt_ptr;


void setup_tables()
{
  gdt_ptr.limit = (sizeof(gdt_struct_t) * 3) - 1;
  gdt_ptr.base = (u32int)&gdt_entry_array;
  
  create_gdt_entry(0, 0, 0, 0, 0);
  create_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  create_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  //create_tss_entry(4, (u32int)&tss_entry);
  
  gdt_flush((u32int)&gdt_ptr);
  
  int i;
  for(i = 0; i < ISR_AMOUNT; i++)
  {
    isr_array[i] = ISR_MACRO_LOC + (4 * i);
  }
}

void create_gdt_entry(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{
  gdt_entry_array[num].low_base 	= base & 0xFFFF;
  gdt_entry_array[num].middle_base 	= (base >> 16) & 0xFF;
  gdt_entry_array[num].high_base	= (base >> 24) & 0xFF;
  gdt_entry_array[num].limit		= limit & 0xFFFF;
  gdt_entry_array[num].gran		= (limit >> 16) & 0x0F;
  gdt_entry_array[num].gran		|= gran & 0xF0;
  gdt_entry_array[num].access		= access;
}

void create_tss_entry(s32int num, u32int base)
{
  create_gdt_entry(num, base, sizeof(tss_struct_t), 0x89, 0x40);
}

void create_idt_entry(u8int num, u32int base, u16int select, u8int flags)
{
  idt_entry_array[num].offsetone = base & 0xFFFF;
  idt_entry_array[num].offsettwo = (base >> 16) & 0xFFFF;
  
  idt_entry_array[num].select = select;
  idt_entry_array[num].attrib = flags;
  idt_entry_array[num].zero   = 0;
}