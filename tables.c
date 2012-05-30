#include "tables.h"

gdt_struct_t gdt_entry_array[4];
gdtptr_struct_t gdt_ptr;
tss_struct_t tss_entry;

void gdt_flush(u32int addr)
{
  asm volatile(".intel_syntax noprefix \n mov eax, [esp+4] \n lgdt [eax] \n mov ax, 0x10 \n");
  asm volatile("mov ds, ax \n mov es, ax \n mov fs, ax \n mov gs, ax \n");
  asm volatile("mov ss, ax \n jmp 0x08:.flush \n .flush: \n .att_syntax prefix \n ret \n");
}

void idt_flush(u32int addr)
{
  asm volatile(".intel_syntax noprefix \n mov eax, [esp+4] \n lidt [eax] \n");
  asm volatile(".att_syntax prefix \n ret \n");
}

void setup_tables()
{
  gdt_ptr.limit = (sizeof(gdt_struct_t) * 4) - 1;
  gdt_ptr.base = (u32int)&gdt_entry_array;
  
  create_gdt_entry(0, 0, 0, 0, 0);
  create_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
  create_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
  create_tss_entry(4, (u32int)&tss_entry);
  
  gdt_flush((u32int)&gdt_ptr);
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