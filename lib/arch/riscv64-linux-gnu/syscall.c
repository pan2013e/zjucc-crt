#include "errno.h"

long syscall(long sys_num, ...) {
	__builtin_va_list ap;
	__builtin_va_start(ap, sys_num);
	register long a7 asm("a7") = sys_num;
	register long a0 asm("a0") = __builtin_va_arg(ap, long);
	register long a1 asm("a1") = __builtin_va_arg(ap, long);
	register long a2 asm("a2") = __builtin_va_arg(ap, long);
	register long a3 asm("a3") = __builtin_va_arg(ap, long);
	register long a4 asm("a4") = __builtin_va_arg(ap, long);
	register long a5 asm("a5") = __builtin_va_arg(ap, long);
	__builtin_va_end(ap);
	asm volatile("scall" : "+r"(a0)
			: "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5), "r"(a7)
		);
	if(a0 < 0) {
        errno = -a0;
        return -1;
    }
	return a0;
}
