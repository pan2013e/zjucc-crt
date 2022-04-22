#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#define __X86_64__

#include "asm/unistd_64.h"

long syscall(int sys_num, ...);

#endif /* _SYSCALL_H_ */