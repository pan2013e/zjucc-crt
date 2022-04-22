long syscall(int sys_num, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, sys_num);
    register long a0 asm("rax") = sys_num;
    register long a1 asm("rdi") = __builtin_va_arg(ap, long);
    register long a2 asm("rsi") = __builtin_va_arg(ap, long);
    register long a3 asm("rdx") = __builtin_va_arg(ap, long);
    register long a4 asm("r10") = __builtin_va_arg(ap, long);
    __builtin_va_end(ap);
    asm volatile("syscall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a3), "r"(a4)
        : "memory", "rcx", "r8", "r9", "r11");
    return a0;
}