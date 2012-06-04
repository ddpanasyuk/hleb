#include "console.h"

static u8int x = 0;
static u8int y = 0;

void kprint(char* str)
{
  u8int i;
  for(i = 0; str[i] != '\0'; i++)
    kput(str[i]);
}

void kprint_hex(u32int num)
{
  int i;
  char byte;
  char is_zero = 0;
  for(i = 28; i> 0; i -= 4)
  {
    byte = (num >> i) & 0xF;
    if(byte == 0 && is_zero == 0)
      continue;
    else
    {
      if(byte <= 0x09)
	kput(byte + 48);
      else
	kput(byte + (97 - 0x0A));
      is_zero = 1;
    }
  }
  byte = num & 0xF;
  if(byte <= 0x09)
    kput(byte + 48);
  else
    kput(byte + (97 - 0x0A));
}

void kput(char byte)
{
  u16int screen_byte = GREY_ON_BLACK << 8 | byte;
  u16int *loc;
  switch(byte)
  {
    case 0x0A: //Newline
      x = 0;
      y++;
      break;
    case 0x08: //backspace
      if(x != 0)
	x--;
      break;
    default: //It's a character
      loc = ((y * 80 + x) * 2) + VIDEO_MEM_START;
      *loc = screen_byte;
      if(x != 80)
	x++;
      else
      {
	x = 0;
	y++;
      }
      break;
  }
  kscroll();
}

void kclear()
{
  u16int *loc = (u16int *)VIDEO_MEM_START;
  u16int byte = 0x00 << 8 | 0x20;
  u32int i;
  for(i = 0; i < 80 * 25; i++)
    loc[i] = byte;
  x = 0;
  y = 0;
}

void kscroll()
{
  u16int *loc = (u16int *)VIDEO_MEM_START;
  u16int byte = 0x00 << 8 | 0x20;
  u32int i;
  if(y >= 25)
  {
    for(i = 0; i < 24 * 80; i++)
      loc[i] = loc[i + 80];
    for(i = 24*80; i < 25 * 80; i++)
      loc[i] = byte;
  y = 24;
  }
}