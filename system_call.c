#include "system_call.h"
#include "stream.h"
#include "console.h"
#include "keyboard.h"

#define SYS_CALLS 8
void *sys_array[SYS_CALLS] = { &kprint, &kprint_hex, &kput, &getchar, &open, &close, &read, &write};

void create_syscall(u8int num)
{
  add_interrupt(num, (void*)&handle_syscall);
}

void handle_syscall(registers_t* regs)
{
  if(regs->eax >= SYS_CALLS)
    return;
  else
  {
    void *call = sys_array[regs->eax];
    u32int call_ret;
    asm volatile("push %1 \npush %2 \npush %3 \npush %4 \npush %5 \ncall *%6 \npop %%ebx \npop %%ebx \npop %%ebx \npop %%ebx \npop %%ebx \n"
		: "=a" (regs->eax) : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx),"r" (regs->ebx), "r" (call));
  }
}
