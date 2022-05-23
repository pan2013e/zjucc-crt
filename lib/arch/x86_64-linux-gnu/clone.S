.section .text
    .global __clone
    .extern __errno_location

__clone:
        movq        $-22, %rax /* -EINVAL */
        subq        $16,  %rsi
        movq        %rcx, 8(%rsi)
        movq        %rdi, 0(%rsi)
        movq        %rdx, %rdi
        movq        %r8,  %rdx
        movq        %r9,  %r8
        mov         8(%rsp), %r10
        movl        $56,  %eax /* SYS_clone */
        syscall
        testq       %rax, %rax
        jl          __syscall_error
        jz          thread_start
__clone_ret:
        ret

__syscall_error:
        neg         %eax
        mov         %eax, %ebx
        mov         $0x0, %eax
        call        __errno_location
        mov         %ebx, (%rax)
        movq        $-1,  %rax
        jmp         __clone_ret

thread_start:
        xorl        %ebp, %ebp
        popq        %rax                /* Function to call.  */
        popq        %rdi                /* Argument.  */
        call        *%rax
        movq        %rax, %rdi
        movl        $60, %eax           /* SYS_exit */
        syscall
