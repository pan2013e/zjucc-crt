#include "stdlib.h"
#include "string.h"
#include "setjmp.h"

#include "coroutine.h"

enum co_status {
    CO_RUNNING,
    CO_SUSPENDED,
    CO_FINISHED
};

typedef unsigned char uint8_t;
typedef struct __co co_impl;

#define STACK_SIZE    (64 * 1024)   /* 64 KiB */
/* Stack grows from high to low in x86_64 ABI */
#define STACK_TOP(co) ((co)->stack + STACK_SIZE)

struct __co {
    char*          name;
    co_func        func;
    void*          arg;

    enum co_status status;
    
    void*          yield_value;
    jmp_buf        context;
    jmp_buf        caller_context;
    uint8_t        stack[STACK_SIZE]; /* Actually allocated in heap area */
};

static co_t current;

/* Switch stack frame, then call `void (*entry)(void* arg)' */
static inline void stack_switch_call(void* sp, void* entry, unsigned long arg) {
    asm volatile (
        #if __x86_64__
            "movq %0, %%rsp\n"
            "movq %2, %%rdi\n"
            "call *%1"
            : : "b"((unsigned long)sp), "d"(entry), "a"(arg) : "memory"
        #else
            #error "Unsupported architecture"
        #endif
    );
}

co_t __co_start(char* __name, co_func __f, void* __arg) {
    co_t new_co = (co_t)malloc(sizeof(co_impl));
    new_co->name = strdup(__name);
    new_co->func = __f;
    new_co->arg = __arg;
    new_co->yield_value = NULL;
    new_co->status = CO_RUNNING;
    current = new_co;
    int res = setjmp(new_co->caller_context); /* Save caller context */
    if (res == 0) {
        stack_switch_call(STACK_TOP(new_co), new_co->func, (unsigned long)new_co->arg);
    }
    return new_co;
}

void co_yield(void* value) {
    current->status = CO_SUSPENDED; /* Mark the state as suspended */
    current->yield_value = value; /* Save the yield value */
    int res = setjmp(current->context);  /* Save the context */
    if (res == 0) {  /* Only reachable when saving context in the coroutine */
        longjmp(current->caller_context, 1); /* Jump back to the caller */
    }
    /* `longjmp' in `co_resume()' will make `setjmp' return 1
     * Then `co_yield' returns and transfers control back to the coroutine
    */
}

void co_return(void* value) {
    current->status = CO_FINISHED; /* Mark the state as finished */
    current->yield_value = value;
    /* In `co_return', we do not save context
     * as the coroutine could not be resumed again
    */
    longjmp(current->caller_context, 1);
}

void co_resume(co_t co) {
    if (!co) return;
    if (co->status == CO_SUSPENDED) { /* Only resume suspended coroutines */
        longjmp(co->context, 1);
    }
}

void co_destroy(co_t co) {
    // TODO: implement `free' in `stdlib.h' first
}

const char* const get_current_co_name() {
    if (!current) return NULL;
    return current->name;
}

void* get_yield_value(co_t co) {
    if (!co) return NULL;
    return co->yield_value;
}