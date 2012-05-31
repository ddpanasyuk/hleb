#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "io.h"
#include "isr.h"
#include "console.h"
//thanks osdev.org
#define PORT_B_REG   0x61
#define PORT_DATA    0x60
#define PORT_STATUS  0x64
#define PORT_COMMAND 0x64

#define BUFFER_EMPTY 0
#define BUFFER_FULL  1
#define NO_ERR 0
#define ERR    1
#define PORT_STATUS_OUTPUT(x)   (x & 0b00000001)
#define PORT_STATUS_INPUT(x)    ((x >> 1) & 0b00000010)
#define PORT_STATUS_COM_OR_DATA ((x >> 3) & 0b00001000)
#define PORT_STATUS_TIMEOUT     ((x >> 6) & 0b01000000)
#define PORT_STATUS_PARITY      ((x >> 7) & 0b10000000)

#define COM_READ_CONFIG 0x20
#define COM_WRITE_CONFIG 0x60

#define ENABLED 1
#define DISABLED 0

#define CONFIG_FIRST_INTERRUPT(x)     (x & 0b00000001)
#define CONFIG_SECOND_INTERRUPT(x)    ((x >> 1) & 0b00000010)
#define CONFIG_FIRST_CLOCK(x)	   ((x >> 4) & 0b00010000)
#define CONFIG_SECOND_CLOCK(x)        ((x >> 5) & 0b00100000)
#define CONFIG_FIRST_TRANSLATION(x)   ((x >> 6) & 0b01000000)

#define COM_READ_CONTROLLER_OUTPUT  0xD0
#define COM_WRITE_CONTROLLER_OUTPUT 0xD1

u8int init_keyboard();
void keyboard_irq(registers_t* regs);

#endif
