#include "stream.h"

FILE* open(char* file_name, u8int flags)
{
  if(file_name == STDIN)
  {
    FILE* stdin = (FILE*)memret(sizeof(FILE));
    *stdin->name = "stdin";
    stdin->file_id = STDIN;
    return stdin;
  }
  if(file_name == STDOUT)
  {
    FILE* stdout = (FILE*)memret(sizeof(FILE));
    *stdout->name = "stdout";
    stdout->file_id = STDOUT;
    return stdout;
  }
  return 0;
}

u8int close(FILE* f_ptr)
{
  return 0;
}

u8int write(FILE* f_ptr, char* buff, u32int len)
{
  int i;
  if(f_ptr->file_id == STDOUT)
    for(i = 0; i < len; i++)
      kput(buff[i]);
  return 0;
}

u8int read(FILE* f_ptr, char* buff, u32int len)
{
  if(f_ptr->file_id == STDIN)
    read_keyboard_buff(buff, len);
  return 0;
}

