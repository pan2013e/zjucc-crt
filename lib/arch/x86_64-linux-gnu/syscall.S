.section .text
    .global write, putchar

# size_t write(int stream, const void* buf, size_t count)
write:
    pushq %rbp
    movq  %rsp,  %rbp
    movl %edx,  %edx
    movq %rsi,  %rcx
    movl %edi,  %ebx
    movl $4,    %eax
    int  $0x80
    popq %rbp
    ret

# int putchar(int ch)
putchar:
    push %rbp
    mov  %rsp,   %rbp
    mov  %rdi,   %rbx
    push %rbx
    mov  $1,     %rax
    mov  $1,     %rdi
    mov  %rsp,   %rsi
    mov  $1,     %rdx
    syscall
    pop  %rbx
    pop  %rbp
    ret
