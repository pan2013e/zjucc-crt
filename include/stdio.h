#ifndef _STDIO_H_
#define _STDIO_H_

typedef void FILE; // opaque type

extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

#define stdin stdin
#define stdout stdout
#define stderr stderr

#define EOF (-1)

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

int puts(char* s);
char* gets(char* buf);
int printf(char* fmt, ...);
int scanf(char* fmt, ...);

int putchar(int ch);
int getchar();

void perror(char* s);

FILE* fopen(char* path, char* mode);
int fprintf(FILE* fp, char* fmt, ...);
int fputs(char* s, FILE* fp);
int fputc(int ch, FILE* fp);
int fgetc(FILE* fp);
char* fgets(char* buf, int n, FILE* fp);
int fclose(FILE* fp);
int fileno(FILE* fp);

#endif /* _STDIO_H_ */