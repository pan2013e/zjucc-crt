#include "syscall.h"

#define EOF (-1)

int getchar() {
    volatile char s;
    int ret = syscall(SYS_read, 0, &s, 1);
    return ret == 0 ? EOF : s;
}