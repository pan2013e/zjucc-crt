
.section .data
__getchar_buf:
    .space 8

.section .text
#    .global write
    .global putchar, getchar

# size_t write(int _fd, const void* buf, size_t size)
#write:
#    pushq %rbp
#    movq  %rsp,  %rbp
#    movl %edx,  %edx
#    movq %rsi,  %rcx
#    movl %edi,  %ebx
#    movl $4,    %eax
#    int  $0x80
#    popq %rbp
#    ret

# int getchar()
getchar:
    pushq %rbp
    movq  %rsp,  %rbp
    movl  $1,  %edx
    movq  $__getchar_buf,  %rcx
    movl  $0,  %ebx
    movl  $3,  %eax
    int   $0x80
    movl  0(%rcx), %eax
    popq  %rbp
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
