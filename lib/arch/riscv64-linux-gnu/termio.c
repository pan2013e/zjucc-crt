#include "syscall.h"

#define EOF (-1)

int putchar(int ch) {
    syscall(SYS_write, 1, &ch, 1);
    return 0;
}

int getchar() {
    volatile char s;
    int ret = syscall(SYS_read, 0, &s, 1);
    return ret == 0 ? EOF : s;
}