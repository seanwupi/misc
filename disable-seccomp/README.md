

### Disable Seccomp

Disable prctl(PR_SET_SECCOMP) on both i386 and x64. 
Just call `no_seccomp()` to initialize.
It's inherited by child process.

