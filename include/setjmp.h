#ifndef _SETJMP_H
#define _SETJMP_H

#if defined __x86_64__ && !defined __ILP32__
/* Offsets:
 * RBX = 0
 * RBP = 1
 * R12 = 2
 * R13 = 3
 * R14 = 4
 * R15 = 5
 * RSP = 6
 * PC  = 7
 */
typedef long __jmp_buf[8];

/* Calling environment */
struct __jmp_buf_tag {
    /* NOTE: This implementation does not save signal mask  */
    __jmp_buf __jmpbuf;		/* Calling environment.  */
};

typedef struct __jmp_buf_tag jmp_buf[1];

/* Store the calling environment in ENV, not saving the signal mask.
   Return 0.  */
int __setjmp(struct __jmp_buf_tag __env[1]);

/* Jump to the environment saved in ENV, making the `setjmp' call there return VAL.  */
void __longjmp(struct __jmp_buf_tag __env[1], int __val) __attribute__((__noreturn__));

#define setjmp(env)	__setjmp(env)
#define longjmp(env, val)	__longjmp((env), (val) ? (val) : 1)

#else
#error "Unsupported architecture"
#endif

#endif // _SETJMP_H