#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include "asm/unistd_32.h"
#include "asm/unistd_64.h"

#if __X86_64__
int syscall_32(int sys_num, ...);
#endif

long syscall(int sys_num, ...);

#endif /* _SYSCALL_H_ */