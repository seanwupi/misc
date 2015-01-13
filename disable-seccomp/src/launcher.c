#include <stdio.h>
#include "seccomp-bpf.h"

char shellcode[4096];

int InitSandbox() {
  alarm(10);
  struct sock_filter filter[] = {
    VALIDATE_ARCHITECTURE,
    EXAMINE_SYSCALL,
    DISALLOW_SYSCALL(execve),
    DEFAULT_ALLOW
  };
  struct sock_fprog prog = {
    .len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
    .filter = filter,
  };

  if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
    perror("prctl(NO_NEW_PRIVS)");
    goto failed;
  }
  if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) {
    perror("prctl(SECCOMP)");
    goto failed;
  }
  return 0;

failed:
  if (errno == EINVAL)
    fprintf(stderr, "SECCOMP_FILTER is not available. :(\n");
  return 1;
}

int main() {
  InitSandbox();
  write(1, "Submit your shellcode here: ", 28);
  read(0, shellcode, sizeof(shellcode));
  ExecuteShellcode(shellcode);
}
