#include "console.h"

u8int x = 0;
u8int y = 0;

void kprint(char* str)
{
  u8int i;
  for(i = 0; str[i] != '\0'; i++)
    kput(str[i]);
}

void kput(char byte)
{
  u16int screen_byte = GREY_ON_BLACK << 8 | byte;
  u16int *loc = ((y * 80 + x) * 2) + VIDEO_MEM_START;
  switch(byte)
  {
    case 0x0A: //Newline
      x = 0;
      y++;
      break;
    default: //It's a character
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
    for(i = 0; i < 24 * 80; i++)
      loc[i] = loc[i + 80];
    for(i = 24*80; i < 25 * 80; i++)
      loc[i] = byte;
  y = 24;
}