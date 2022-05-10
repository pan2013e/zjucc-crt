.section .init
    .global _init
_init:
    push    %rbp
    movq    %rsp, %rbp
    popq    %rbp
    ret

.section .text
    .extern __malloc_init, exit
    .global _start, _exit

_start :
    pushq   %rbp
    movq    %rsp, %rbp
    movq    0(%rbp), %rdi
    leaq    8(%rbp), %rsi
    pushq   %rcx  # envp
    pushq   %rsi  # argv
    pushq   %rdi  # argc
    call _init
    call __malloc_init
    popq    %rdi
    popq    %rsi
    popq    %rcx
    call _main

_main:
    pushq	%rax
	popq	%rax
	subq	$8, %rsp
	call	main
	movl	%eax, %edi
	call	exit

_exit:
    movq    %rax,  %rbx
    movq    $1,    %rax
    int     $0x80
    ret

.section .fini
    .global _fini
_fini:
    pushq   %rbp
    movq    %rsp, %rbp
    popq    %rbp
    ret
