
#include "isr.h"

void isr_handler(registers_t regs)
{
    kprint("interrupt: ");
    kprint_hex(regs.int_no);
    kput('\n');
}
