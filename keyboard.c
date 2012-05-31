#include "keyboard.h" 

u8int init_keyboard()
{
  u8int test = 0;
  u8int num_channel = 1;
  asm volatile("cli");
  out(PORT_COMMAND, 0xAD);
  out(PORT_COMMAND, 0xA7);
  in(PORT_DATA); //Disable devices and clean outport port
  
  out(PORT_COMMAND, 0x20); //Get current config
  u8int temp = in(PORT_DATA);
  //if(CONFIG_SECOND_CLOCK(temp)) // is it a dual channel devices
  //  num_channel = 2;
    
  //kprint_hex(temp);
  
  temp &= 0b10111100;
  u8int config = temp;
  out(PORT_COMMAND, 0x60);
  out(PORT_DATA, temp);
  
  out(PORT_COMMAND, 0xAA);
  do{test = in(PORT_COMMAND);}while(!(test & 0b00000001));
  temp = in(PORT_DATA);
  if(temp == 0x55)
    kprint("controller self test success \n\0");
  
  out(PORT_COMMAND, 0xAB);
  do{test = in(PORT_COMMAND);}while(!(test & 0b00000001));
  temp = in(PORT_DATA);
  if(temp == 0x55)
    kprint("first ps/2 port working \n\0");
  
  out(PORT_COMMAND, 0xAE);
  
  config |= 0b00000001;
  out(PORT_COMMAND, 0x60);
  do{test = in(PORT_COMMAND);}while(test & 0b00000010);
  out(PORT_DATA, config);
  
  out(PORT_COMMAND, 0x20);
  temp = in(PORT_DATA);
  kprint_hex(temp);
  
  out(0xD1, 0xFF);
  temp = in(PORT_DATA);
  if(temp == 0xFA)
    kprint("success\n\0");
  
  add_interrupt(IRQ1, (void*)&keyboard_irq);
}

void keyboard_irq(registers_t* regs)
{
  regs->eax = in(PORT_DATA);
  kprint("keyboard IRQ fired\n\0");
}