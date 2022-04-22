#include "syscall.h"

int fork() {
    return syscall(SYS_fork);
}

int getpid() {
    return syscall(SYS_getpid);
}

char* getcwd(char* __buf, int __size) {
    int ret = syscall(SYS_getcwd, __buf, __size);
    if (ret < 0) return (void*)0;
    else return __buf;
}

int chdir(char* __path) {
    return syscall(SYS_chdir, __path);
}
