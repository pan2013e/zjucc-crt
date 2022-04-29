
.section .text
	.global _start

_start:
	li a0, 0
	lw a0, 0(sp)
	addi a1, sp, 8
	li a2, 0
	call main
	mv ra, a0
	li a7, 93
	scall
