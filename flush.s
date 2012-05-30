[GLOBAL gdt_flush]
gdt_flush:
mov eax, [esp + 4]
lgdt [eax]
ret

[GLOBAL idt_flush]
idt_flush:
mov eax, [esp + 4]
lidt [eax]
ret