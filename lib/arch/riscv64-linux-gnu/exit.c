#include "syscall.h"

void _exit(int rval) {
    syscall(SYS_exit, rval);
}