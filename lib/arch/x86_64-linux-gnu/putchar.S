.section .text
    .global putchar

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
