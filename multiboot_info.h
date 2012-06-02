#ifndef _MULTIBOOT_INFO_H_
#define _MULTIBOOT_INFO_H_

struct multiboot_info
{
  //name  - offset
  u32int flags; //0
  u32int mem_lower; //4
  u32int mem_upper; //8
  u32int boot_device; //12
  u32int cmdline; //16
  u32int mods_count; //20
  u32int mods_addr; //24
  u32int syms_one; //28
  u32int syms_two; //32
  u32int syms_three; //36
  u32int syms_four; //40
  u32int mmap_length; //44
  u32int mmap_addr; //48
  u32int drives_length; //52
  u32int drives_addr; //56
  u32int config_table; //60
  u32int boot_loader_name; //64
  u32int apm_table; //68
  u32int vbe_control_info; //72
  u32int vbe_mode_info; //76
  u16int vbe_mode; //80
  u16int vbe_interface_seg; //82
  u16int vbe_interface_off; //84
  u16int vbe_interface_len; //86
}__attribute__((packed));
typedef struct multiboot_info multiboot_info_t;

struct multiboot_module
{
  u32int addr_start;
  u32int addr_end;
  
  u32int cmdline;
  u32int pad;
}__attribute__((packed));
typedef struct multiboot_module multiboot_module_t;

#endif
