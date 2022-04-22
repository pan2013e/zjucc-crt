#ifndef _STDIO_H_
#define _STDIO_H_

#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int putchar(int ch);
int puts(char* s);
int puti(int n);

int getchar();
int gets(char* buf);

#endif /* _STDIO_H_ */