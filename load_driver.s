[global prog_load];takes two arguments, address to load at + address from which to load
prog_load:
mov eax, [esp + 4]; load address
mov ebx, [esp + 8]; target address

load_loop:
  mov dl, [ebx]
  cmp dl, 0x55
  jne no_end
  mov dl, [ebx + 1]
  cmp dl, 0xAA
  je run
  no_end:
  mov [eax], dl
  inc eax
  inc ebx
  jmp load_loop

run:
mov ebx, [esp + 4]
push ebx
call ebx
add esp, 4
ret

