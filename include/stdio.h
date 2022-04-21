#ifndef _STDIO_H_
#define _STDIO_H_

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

typedef long size_t;

int write(int _fd, const void* buf, size_t size);

int putchar(int ch);

#endif /* _STDIO_H_ */