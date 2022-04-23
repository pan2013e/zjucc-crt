#include "syscall.h"
#include "stdio.h"

#define MMAP_THRESHOLD 128*1024
#define MAX_HEAP_SIZE  64*1024*1024
#define NULL (void*)0

static int __malloc_initialized = 0;
static void* brkp = NULL;
static void* startp = NULL;
static void* endp = NULL;

void __malloc_init() {
    startp = (void*)syscall(SYS_brk, 0);
    brkp = startp;
    endp = (void*)syscall(SYS_brk, (unsigned long)startp + MAX_HEAP_SIZE);
    __malloc_initialized = 1;
}

static void* sbrk(int __incr) {
    if (__incr == 0) {
        return brkp;
    }
    void* __original = brkp;
    brkp = (void*)((unsigned long)brkp + __incr);
    if (brkp >= endp || brkp < startp) {
        return NULL;
    }
    return __original;
}

void* malloc(int __size) {
    return sbrk(__size);
}