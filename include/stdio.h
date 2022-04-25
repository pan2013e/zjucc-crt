#ifndef _STDIO_H_
#define _STDIO_H_

#define putcln(s)  putchar(s); putchar('\n');
#define putsln(s)  puts(s); putchar('\n');
#define putiln(s)  puti(s); putchar('\n');
#define putfln(s)  putf(s); putchar('\n');

int putchar(int ch);
int puts(char* s);
int puti(long n);
int putf(double x);

int getchar();
int gets(char* buf);

#endif /* _STDIO_H_ */