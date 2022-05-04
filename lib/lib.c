#include "stdio.h"

extern void _exit(int);

void exit(int __status) {
    _exit(__status);
}

int __assert(char* msg, char* file, int line) {
    printf("Assertion failed: %s at %s, line %d\n", msg, file, line);
    exit(-1);
}