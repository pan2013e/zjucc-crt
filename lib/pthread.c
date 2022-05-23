#include "pthread.h"
#include "stdlib.h"
#include "sys/sched.h"

#define MAX_THREADS 128
#define STACK_SIZE  (64 * 1024)
#define STACK_TOP(thread) ((thread)->stack + STACK_SIZE)

/* We rely heavily on various flags the CLONE function understands:
     CLONE_VM, CLONE_FS, CLONE_FILES
        These flags select semantics with shared address space and
        file descriptors according to what POSIX requires.
     CLONE_SIGHAND, CLONE_THREAD
        This flag selects the POSIX signal semantics and various
        other kinds of sharing (itimers, POSIX timers, etc.).
     CLONE_SETTLS
        The sixth parameter to CLONE determines the TLS area for the
        new thread.
     CLONE_PARENT_SETTID
        The kernels writes the thread ID of the newly created thread
        into the location pointed to by the fifth parameters to CLONE.
        Note that it would be semantically equivalent to use
        CLONE_CHILD_SETTID but it is be more expensive in the kernel.
     CLONE_CHILD_CLEARTID
        The kernels clears the thread ID of a thread that has called
        sys_exit() in the location pointed to by the seventh parameter
        to CLONE.
     The termination signal is chosen to be zero which means no signal
     is sent. */
#define CLONE_FLAGS \
    (CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SYSVSEM \
        | CLONE_SIGHAND | CLONE_THREAD \
        | CLONE_SETTLS | CLONE_PARENT_SETTID \
        | CLONE_CHILD_CLEARTID \
        | 0);

typedef unsigned char uint8_t;

typedef struct pthread_impl pthread_impl;
struct pthread_impl {
    pthread_t tid;
    const pthread_attr_t* attr;
    void* (*start_routine)(void*);
    uint8_t stack[STACK_SIZE];
    void* arg;
    void* ret;
};

pthread_impl threads[MAX_THREADS];
int n_threads = 0;

static int do_clone(pthread_impl* thread) {
    return clone(thread->start_routine, STACK_TOP(thread),
        CLONE_THREAD, thread->arg);
}

int pthread_create(pthread_t* thread, const pthread_attr_t* attr,
    void* (*start_routine)(void*), void* arg) {
    pthread_impl new_thread = {
        .tid  = n_threads,
        .attr = attr,
        .start_routine = start_routine,
        .arg  = arg,
        .ret  = NULL
    };
    threads[n_threads++] = new_thread;
    if(thread) *thread = new_thread.tid;
    return do_clone(&new_thread);
}