section .data
global _start
_start:
  jmp En
St:
  xor eax,eax
  pop ebx
  mov [ebx+7], al
  lea ecx, [ebx+8]
  lea edx, [ebx+12]
  mov [ecx], ebx
  mov [edx], eax
  mov al, 11
  int 0x80
En:
  call St
  db '/bin/sh',0xa
