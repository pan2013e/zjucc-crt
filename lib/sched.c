#include "stdlib.h"
#include "stdio.h"
#include "sys/sched.h"
#include "syscall.h"
#include "errno.h"
#include "unistd.h"

extern int __clone(int (*__fn) (void* __arg), void* __child_stack,
    int __flags, void* __arg, ...);

int clone(int (*__fn) (void* __arg), void* __child_stack,
    int __flags, void* __arg, ...) {
    if (__fn == NULL || __child_stack == NULL) { // check invalid pointers
        errno = EINVAL;
        return -1;
    }
    return __clone(__fn, __child_stack, __flags, __arg);
}