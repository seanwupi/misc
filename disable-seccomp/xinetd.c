#include <unistd.h>
#include "sandbox.h"

int main(int argc, char **argv, char **envp) {
  no_seccomp();
  execve("/usr/sbin/xinetd.orig", argv, envp);
}
