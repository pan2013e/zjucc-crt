.text
    .global write

# write(int stream, const void* buf, size_t count);
write:
    movq %rdx,  %rdx # size
    movq %rsi,  %rcx # buf
    movq %rdi,  %rbx # stream
    movl $4,    %eax # write() is the 4th syscall
    int  $0x80
    ret
