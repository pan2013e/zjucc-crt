.section .text
    .global __setjmp, __longjmp

# int __setjmp (struct __jmp_buf_tag __env[1]);
__setjmp:
    xor %esi, %esi
    # context save
    mov %rbx, (%rdi)     # save RBX
    mov %rbp, 0x8(%rdi)  # save RBP
    mov %r12, 0x10(%rdi) # save R12
    mov %r13, 0x18(%rdi) # save R13
    mov %r14, 0x20(%rdi) # save R14
    mov %r15, 0x28(%rdi) # save R15
    lea 0x8(%rsp), %rdx  # original RSP when setjmp was called
    mov %rdx, 0x30(%rdi) # save RSP
    mov (%rsp), %rax     # get PC where setjmp was called
    mov %rax, 0x38(%rdi) # save PC
    xor %eax, %eax       # return 0
    retq


# void longjmp (struct __jmp_buf_tag __env[1], int __val);
__longjmp:
    # context restore
    mov (%rdi), %rbx     # restore RBX
    mov 0x8(%rdi), %rbp  # restore RBP
    mov 0x10(%rdi), %r12 # restore R12
    mov 0x18(%rdi), %r13 # restore R13
    mov 0x20(%rdi), %r14 # restore R14
    mov 0x28(%rdi), %r15 # restore R15
    mov 0x30(%rdi), %rsp # restore RSP
    mov %esi, %eax       # `setjmp' returns `__val'
    mov 0x38(%rdi), %rdx # get PC
    jmpq *%rdx           # jump to PC

