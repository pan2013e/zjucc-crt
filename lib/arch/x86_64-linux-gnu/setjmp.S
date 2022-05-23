.section .text
    .global __setjmp, __longjmp

# int __setjmp (struct __jmp_buf_tag __env[1]);
__setjmp:
    xor %esi, %esi
    # context save
    mov %rbx, (%rdi)  # save RBX
    # encrypt RBP, CVE-2013-4788
    mov %rbp, %rax
    xor %fs:0x30, %rax
    rol $0x11, %rax
    mov %rax, 0x8(%rdi)  # save RBP
    mov %r12, 0x10(%rdi) # save R12
    mov %r13, 0x18(%rdi) # save R13
    mov %r14, 0x20(%rdi) # save R14
    mov %r15, 0x28(%rdi) # save R15
    lea 0x8(%rsp), %rdx  # original RSP when setjmp was called
    # encrypt RSP
    xor %fs:0x30, %rdx
    rol $0x11, %rdx
    mov %rdx, 0x30(%rdi) # save RSP
    mov (%rsp), %rax     # get PC where setjmp was called
    # encrypt PC
    xor %fs:0x30, %rax
    rol $0x11, %rax
    mov %rax, 0x38(%rdi) # save PC
    xor %eax, %eax       # return 0
    retq


# void longjmp (struct __jmp_buf_tag __env[1], int __val);
__longjmp:
    mov 0x30(%rdi), %r8  # get encrypted RSP
    mov 0x8(%rdi),  %r9  # get encrypted RBP
    mov 0x38(%rdi), %rdx # get encrypted PC
    # decrypt RSP
    ror $0x11, %r8
    xor %fs:0x30, %r8
    # decrypt RBP
    ror $0x11, %r9
    xor %fs:0x30, %r9
    # decrypt PC
    ror $0x11, %rdx
    xor %fs:0x30, %rdx
    # context restore
    mov (%rdi), %rbx    # restore RBX
    mov %r9, %rbp       # restore RBP
    mov 0x10(%rdi), %r12 # restore R12
    mov 0x18(%rdi), %r13 # restore R13
    mov 0x20(%rdi), %r14 # restore R14
    mov 0x28(%rdi), %r15 # restore R15
    mov %r8, %rsp       # restore RSP
    mov %esi, %eax      # return __val
    jmpq *%rdx           # jump to PC

