[section .text]
global ExecuteShellcode
ExecuteShellcode:
  mov eax, [esp+4]
  call eax
  ret
