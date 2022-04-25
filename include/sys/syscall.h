#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#define __X86_64__

#include "asm/unistd_32.h"
#include "asm/unistd_64.h"

int syscall_32(int sys_num, ...);
long syscall(int sys_num, ...);

#endif /* _SYSCALL_H_ */