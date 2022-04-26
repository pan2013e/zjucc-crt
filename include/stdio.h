#ifndef _STDIO_H_
#define _STDIO_H_

#ifdef HAS_POINTER
int puts(char* s);
int gets(char* buf);
int printf(char* fmt, ...);
#else
#define puts(s) printf("%s\n", s)
#define printf(fmt, ...) __builtin_printf(fmt, ##__VA_ARGS__)
#endif

int puti(int n);
int putf(double x);

int putchar(int ch);
int getchar();

#endif /* _STDIO_H_ */