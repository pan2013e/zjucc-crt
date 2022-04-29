#include "syscall.h"

int putchar(int ch) {
    char s[2] = { ch,0 };
    syscall(SYS_write, 1, s, 1);
    return 0;
}

int getchar() {
    char s[2] = { 0 };
    syscall(SYS_read, 0, s, 1);
    return s[0];
}