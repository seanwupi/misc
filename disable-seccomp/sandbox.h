#include <stdio.h>
#include <stddef.h>
#include <errno.h>
#include <linux/unistd.h>
#include <linux/seccomp.h>
#include <linux/filter.h>
#include <linux/audit.h>
#include <sys/prctl.h>

#define arch_nr (offsetof(struct seccomp_data, arch))
#define syscall_nr (offsetof(struct seccomp_data, nr))
#define syscall_arg_0 (offsetof(struct seccomp_data, args[0]))

void no_seccomp() {
  struct sock_filter filter[] = {
    BPF_STMT(BPF_LD+BPF_W+BPF_ABS, arch_nr), 
    BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, AUDIT_ARCH_I386, 0, 2), 
    BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_nr),
    BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, 172, 2, 5), //32
    BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_nr),
    BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, 157, 0, 3), //64
    BPF_STMT(BPF_LD+BPF_W+BPF_ABS, syscall_arg_0),
    BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, PR_SET_SECCOMP, 0, 1),
    BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ERRNO|ENOSYS),
    BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)
  };
  struct sock_fprog prog = {
    .len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
    .filter = filter,
  };

  prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
  prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog);
}

