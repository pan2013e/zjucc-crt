#ifndef _STDIO_H_
#define _STDIO_H_

int puts(char* s);
int gets(char* buf);
int printf(char* fmt, ...);

int puti(int n);
int putf(double x);

int putchar(int ch);
int getchar();

void perror(char* s);

#endif /* _STDIO_H_ */