#include "syscall.h"
#include "unistd.h"
#include "sys/time.h"

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

int wait(int* __wstatus) {
    return waitpid(-1, __wstatus, 0);
}

int waitpid(int __pid, int* __wstatus, int __options) {
    return syscall_32(__NR_waitpid, __pid, __wstatus, __options);
}

static int nanosleep(const struct timespec* __req, struct timespec* __rem) {
    return syscall(SYS_nanosleep, __req, __rem);
}

int sleep(int __seconds) {
    struct timespec __req = { __seconds,0 };
    return nanosleep(&__req, (void*)0);
}

int read(int __fd, void* __buf, int __size) {
    return syscall(SYS_read, __fd, __buf, __size);
}

int close(int __fd) {
    return syscall(SYS_close, __fd);
}