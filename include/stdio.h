#ifndef _STDIO_H_
#define _STDIO_H_

typedef void FILE; // opaque type

int puts(char* s);
int gets(char* buf);
int printf(char* fmt, ...);

int puti(int n);
int putf(double x);

int putchar(int ch);
int getchar();

void perror(char* s);

FILE* fopen(char* path, char* mode);
int fputs(FILE* fp, char* s);
int fputc(FILE* fp, int ch);
int fgets(FILE* fp, char* buf, int n);
int fclose(FILE* fp);

#endif /* _STDIO_H_ */