#ifndef _COROUTINE_H_
#define _COROUTINE_H_

typedef struct __co* co_t;

typedef void (*co_func)(void*);

#define co_start(func, arg) \
    __co_start(#func, func, arg);

#define co_await(func, arg) \
    get_yield_value(__co_start(#func, func, arg))

co_t __co_start(char* __name, co_func __f, void* __arg);
void co_resume(co_t co);
void co_return(void* value);
void co_yield(void* value);
void co_destroy(co_t co);

void* get_yield_value(co_t co);
const char* const get_current_co_name();

#endif // _COROUTINE_H_