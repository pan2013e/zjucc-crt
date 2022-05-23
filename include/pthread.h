#ifndef _PTHREAD_H
#define _PTHREAD_H

typedef unsigned long pthread_t;

#if __x86_64__
#  define __SIZEOF_PTHREAD_MUTEX_T 40
#  define __SIZEOF_PTHREAD_ATTR_T 56
#  define __SIZEOF_PTHREAD_RWLOCK_T 56
#  define __SIZEOF_PTHREAD_BARRIER_T 32
#else
#error "Unsupported architecture"
#endif

typedef union pthread_attr_t pthread_attr_t;
union pthread_attr_t {
    char __size[__SIZEOF_PTHREAD_ATTR_T];
    long int __align;
};

int pthread_create(pthread_t* thread, const pthread_attr_t* attr,
    void* (*start_routine)(void*), void* arg);

#endif // _PTHREAD_H