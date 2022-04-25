#include "stdio.h"

extern void _exit(int);

void exit(int __status) {
    _exit(__status);
}

int __assert(char* msg, char* file, int line) {
    puts("Assertion failed: ");
    puts(msg);
    puts(" at ");
    puts(file);
    puts(", line ");
    puti(line);
    putsln("");
    exit(-1);
}