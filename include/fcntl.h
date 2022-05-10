#ifndef _FCNTL_H_
#define _FCNTL_H_

#include "sys/fcntl.h"
#include "bits/types.h"

__mode_t umask(__mode_t __mask);
int open(const char* __path, int __oflags, int __mode);
int creat(const char* __path, int __mode);

#endif /* _FCNTL_H_ */