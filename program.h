#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "stream.h"

#define PIC    0
#define DRIVER 1
#define PDC    2

u8int load_executable(char* filename, u8int flags, u32int argc, char* argv[]);

#endif
