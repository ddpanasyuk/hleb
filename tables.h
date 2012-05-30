#ifndef _TABLES_H_
#define _TABLES_H_

#include "size.h"

struct gdt_struct
{
  u16int limit;
  u16int low_base;
  u8int  middle_base;
  u8int  access;
  u8int  gran;
  u8int  high_base;
}__attribute__((packed));
typedef struct gdt_struct gdt_struct_t;

struct gdtptr_struct
{
  u16int limit;
  u32int base;
}__attribute__((packed));
typedef struct gdtptr_struct gdtptr_struct_t;

struct tss_struct
{
  u32int reserved;
  u32int esp0;
  u32int ss0;
  u32int esp1;       // Unused...
  u32int ss1;
  u32int esp2;
  u32int ss2;
  u32int cr3;
  u32int eip;
  u32int eflags;
  u32int eax;
  u32int ecx;
  u32int edx;
  u32int ebx;
  u32int esp;
  u32int ebp;
  u32int esi;
  u32int edi;
  u32int es;         
  u32int cs;        
  u32int ss;      
  u32int ds;        
  u32int fs;    
  u32int gs;      
  u32int ldt;        
  u16int trap;
  u16int iopb;
}__attribute__((packed));
typedef struct tss_struct tss_struct_t;

struct idt_struct
{
  u16int offsetone;
  u16int select;
  u8int  zero;
  u8int  attrib;
  u16int offsettwo;
}__attribute__((packed));
typedef struct idt_struct idt_struct_t;

struct idtptr_struct
{
  u16int limit;
  u16int base;
}__attribute__((packed));
typedef struct idtptr_struct idtptr_struct_t;

void setup_tables();

void create_gdt_entry(s32int num, u32int base, u32int limit, u8int access, u8int gran);
void create_idt_entry(u8int num, u32int base, u16int select, u8int flags);
void create_tss_entry(s32int num, u32int base);

#define ISR_AMOUNT 31
//Array for our ISRs
void (*isr_array[ISR_AMOUNT])();


#endif
