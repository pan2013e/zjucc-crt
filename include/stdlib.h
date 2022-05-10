#ifndef _STDLIB_H_
#define _STDLIB_H_

#define NULL ((void*)0)
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define assert(EX) ((EX) || (__assert (#EX, __FILE__, __LINE__), 0))

int atexit(void (*func)(void));

void srand(long s);
long rand();

void* malloc(int __size);

void exit(int __status);
int __assert(char* msg, char* file, int line);

#endif /* _STDLIB_H_ */