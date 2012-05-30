;Thanks JamesM for macro definitions 
 %macro ISR_NOERRCODE 1
  isr%1:
    cli                        
    push byte 0                 
    push byte %1                
    jmp isr_handler_asm        
%endmacro


%macro ISR_ERRCODE 1
  isr%1:
    cli                         
    push byte %1                
    jmp isr_handler_asm
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

extern handle_interrupt

isr_handler_asm:
  pusha
  
  call handle_interrupt
  
  popa
  add esp, 8
  sti
  iret
  
global ISR_MACRO_LOC
ISR_MACRO_LOC: ;Our C code will use this to make an array of interrupts
dd isr0
dd isr1
dd isr2
dd isr3
dd isr4
dd isr5
dd isr6
dd isr7
dd isr8
dd isr9
dd isr10
dd isr11
dd isr12
dd isr13
dd isr14
dd isr15
dd isr16
dd isr17
dd isr18
dd isr19
dd isr20
dd isr21
dd isr22
dd isr23
dd isr24
dd isr25
dd isr26
dd isr27
dd isr28
dd isr29
dd isr30
dd isr31