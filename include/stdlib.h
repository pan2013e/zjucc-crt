#ifndef _STDLIB_H_
#define _STDLIB_H_

#define assert(EX) ((EX) || (__assert (#EX, __FILE__, __LINE__), 0))

void srand(long s);
long rand();

void* malloc(int __size);

void exit(int __status);
int __assert(char* msg, char* file, int line);

#endif /* _STDLIB_H_ */