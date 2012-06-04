#ifndef _STREAM_H_
#define _STREAM_H_

#include "console.h"
#include "keyboard.h"
#include "mem.h"

#define STDIN  0
#define STDOUT 1

#define READ   0
#define WRITE  1
#define RW     2
#define APPEND 4
#define CREATE 8

struct file
{
  char name[16];
  u32int file_id;
  u32int start;
  u32int end;
  char* loc;
};
typedef struct file FILE;

FILE* open(char* file_name, u8int flags);
u8int close(FILE* f_ptr);

u8int write(FILE* f_ptr, char* buff, u32int len);
u8int read(FILE* f_ptr, char* buff, u32int len);

#endif
