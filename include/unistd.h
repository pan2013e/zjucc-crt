#ifndef _UNISTD_H_
#define _UNISTD_H_

#include "bits/types.h"

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/* Values for the WHENCE argument to lseek.  */
#ifndef	_STDIO_H_		/* <stdio.h> has the same definitions.  */
# define SEEK_SET	0	/* Seek from beginning of file.  */
# define SEEK_CUR	1	/* Seek from current position.  */
# define SEEK_END	2	/* Seek from end of file.  */
#endif

int write(int __fd, void* __buf, int __size);
int read(int __fd, void* __buf, int __size);
int close(int __fd);

int fork();
int getpid();

int wait(int* __wstatus);
int waitpid(int __pid, int* __wstatus, int __options);

char* getcwd(char* __buf, int __size);
int chdir(char* __path);

int sleep(int __seconds);

__off_t lseek(int __fd, __off_t __offset, int __whence);

#endif /* _UNISTD_H_ */