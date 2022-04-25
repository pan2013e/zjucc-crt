#include "fcntl.h"
#include "syscall.h"
#include "stdlib.h"

int open(const char* __path, int __oflags, int __mode) {
    return syscall(SYS_open, __path, __oflags, __mode);
}

int creat(const char* __path, int __mode) {
    return open(__path, O_CREAT | O_WRONLY | O_TRUNC, __mode);
}