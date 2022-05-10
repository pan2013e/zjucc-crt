#include "stdio.h"
#include "stdlib.h"
#include "syscall.h"

extern void _exit(int);

#define EXIT_REGISTER_LIMIT 0x20
static void (*__atexit[EXIT_REGISTER_LIMIT])(void) = { NULL };
static int __atexit_count = 0;

int atexit(void (*func)(void)) {
    if(__atexit_count >= EXIT_REGISTER_LIMIT) {
        return -1;
    }
    __atexit[__atexit_count++] = func;
    return 0;
}

void exit(int __status) {
    for(int i = __atexit_count - 1; i >= 0; i--) {
        __atexit[i]();
    }
    _exit(__status);
}

int __assert(char* msg, char* file, int line) {
    printf("Assertion failed: %s at %s, line %d\n", msg, file, line);
    exit(-1);
}