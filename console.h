#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "io.h"

#define VIDEO_MEM_START 0xB8000
#define GREY_ON_BLACK 0x07

void kprint(char* str);
void kprint_hex(u32int num);
void kput(char byte);
void kclear();
void kscroll();

#endif
