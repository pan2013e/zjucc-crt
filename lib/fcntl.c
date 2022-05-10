#include "fcntl.h"
#include "syscall.h"
#include "stdlib.h"

__mode_t umask(__mode_t __mask) {
    return syscall(SYS_umask, __mask & 0777);
}

int open(const char* __path, int __oflags, int __mode) {
    return syscall(SYS_open, __path, __oflags, __mode & ~umask(0));
}

int creat(const char* __path, int __mode) {
    return open(__path, O_CREAT | O_WRONLY | O_TRUNC, __mode & ~umask(0));
}