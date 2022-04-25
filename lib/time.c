#include "sys/time.h"
#include "syscall.h"

long clock() {
    struct timespec __tp = { 0, 0 };
    return syscall(SYS_clock_gettime, CLOCK_PROCESS_CPUTIME_ID, &__tp) < 0 ?
        -1 : __tp.tv_sec * CLOCKS_PER_SEC + __tp.tv_nsec / 1000;
}

long time() {
    struct timespec __tp = { 0,0 };
    return syscall(SYS_clock_gettime, CLOCK_REALTIME, &__tp) < 0 ?
        -1 :  __tp.tv_sec;
}