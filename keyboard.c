#include "keyboard.h" 

unsigned char kbdus[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};		

u8int shift_l = 0;
u8int shift_r = 0;
u8int new_key = 0;
u8int echo = 1;

u32int input_storage[256];

u8int init_keyboard()
{
  add_interrupt(IRQ1, (void*)&keyboard_irq);
}

void keyboard_irq(registers_t* regs)
{
  unsigned char scan_code = in(0x60);
  unsigned char ascii_char;
  if(scan_code & 0x80)
  {
    switch(scan_code)
    {
      case 0xB6: //right shift
	shift_r = 0;
	break;
      case 0xAA: //left shift
	shift_l = 0;
	break;
    }
  }
  else
  {
    switch(scan_code)
    {
      case 0x36: //right shift
	shift_r = 1;
	break;
      case 0x2A: //left shit
	shift_l = 1;
	break;
      case 0x0E: //backspace
	kput(0x08);
	kput(' ');
	kput(0x08);
	break;
      default:
	ascii_char = kbdus[scan_code];
	if(shift_l == 1 || shift_r == 1)
	  ascii_char -= 32;
	if(echo == 1)
	  kput(ascii_char);
	int i;
	for(i = 0; i < 256; i++)
	  input_storage[i + 1] = input_storage[i];
	input_storage[0] = (u32int)ascii_char;
	break;
    }
    //kput(kbdus[scan_code]);
  }
}

u8int change_settings(u8int config)
{
  if(config & ECHO)
    echo = (~echo) & ECHO;
}

u8int getchar()
{
  u8int ret_char;
  do{
  }while(input_storage[0] == 0);
  if(input_storage[0])
  {
    ret_char = (u8int)input_storage[0];
    int i;
    for(i = 0; i < 256; i++)
      input_storage[i] = input_storage[i + 1];
    return ret_char;
  }
}