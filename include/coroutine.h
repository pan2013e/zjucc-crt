#ifndef _COROUTINE_H_
#define _COROUTINE_H_

typedef struct co* co_t;

co_t co_start(const char* __name, void (*__f)(void*), void* __arg);
void co_yield();
void co_wait(co_t co);

#endif // _COROUTINE_H_