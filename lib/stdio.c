#include "string.h"
#include "errno.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"

#define NULL (void*)0

typedef struct FILE_IMPL* FILE_PTR;
struct FILE_IMPL {
    int fd;
    int oflags;
    int offset;
    char buffer[1024];
};

int puts(char* s) {
    char* p = s;
    while (*p != '\0') {
        putchar(*p++);
    }
    return 0;
}

int puti(int n) {
    char s[25] = { 0 };
    int pos = 0;
    long num = n;
    if (n < 0) {
        putchar('-');
        num = -num;
    }
    do {
        s[pos++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    for (int i = pos;i >= 0;i--) {
        putchar(s[i]);
    }
    return 0;
}

int putf(double x) {
    int precision = 6, bias = 1e6;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    long temp = (long)(x * bias);
    if (temp != 0) {
        puti(x);
        putchar('.');
        puti(temp % bias);
    } else {
        puti(0);
    }
    return 0;
}

int gets(char* buf) {
    char* p = buf;
    char ch;
    while ((ch = getchar()) != '\n') {
        *buf++ = ch;
    }
    *buf = '\0';
    return 0;
}

int printf(char* fmt, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    char ch;
    while (ch = *fmt++) {
        if (ch != '%') {
            putchar(ch);
            continue;
        } else { // ch == '%'
            if (*fmt == '*') {
                int n_spaces = __builtin_va_arg(ap, int);
                for (int i = 0;i < n_spaces;i++) {
                    putchar(' ');
                }
                fmt++;
            }
            switch (*fmt) {
                case 'c': {
                    int _ch = __builtin_va_arg(ap, int);
                    putchar(_ch);
                    fmt++;
                    break;
                }
                case 's': {
                    char* s = __builtin_va_arg(ap, char*);
                    puts(s);
                    fmt++;
                    break;
                }
                case 'd': {
                    int d = __builtin_va_arg(ap, int);
                    puti(d);
                    fmt++;
                    break;
                }
                case 'f': {
                    double f = __builtin_va_arg(ap, double);
                    putf(f);
                    fmt++;
                    break;
                }
                case '%': {
                    putchar('%');
                    fmt++;
                    break;
                }
                default: {
                    puts("\nUnknown format '%");
                    putchar(*fmt);
                    puts("'\n");
                    return -1;
                }
            }
        }
    }
    __builtin_va_end(ap);
    return 0;
}

void perror(char* s) {
    printf("%s: %s\n", s, strerror(errno));
}

FILE* fopen(char* path, char* mode) {
    FILE_PTR ret = (FILE_PTR)malloc(sizeof(struct FILE_IMPL));
    if (ret == NULL) {
        perror("malloc");
        return NULL;
    }
    int oflags = 0;
    switch (strlen(mode)) {
        case 1: {
            switch (*mode) {
                case 'r': {
                    oflags = O_RDONLY;
                    break;
                }
                case 'w': {
                    oflags = O_WRONLY | O_CREAT | O_TRUNC;
                    break;
                }
                case 'a': {
                    oflags = O_WRONLY | O_CREAT | O_APPEND;
                    break;
                }
                default: {
                    puts("Unknown mode");
                    return NULL;
                }
            }
            break;
        }
        case 2: {
            switch (mode[0]) {
                case 'r': {
                    switch (mode[1]) {
                        case '+': {
                            oflags = O_RDWR;
                            break;
                        }
                        default: {
                            puts("Unknown mode");
                            return NULL;
                        }
                    }
                    break;
                }
                case 'w': {
                    switch (mode[1]) {
                        case '+': {
                            oflags = O_RDWR | O_CREAT | O_TRUNC;
                            break;
                        }
                        default: {
                            puts("Unknown mode");
                            return NULL;
                        }
                    }
                    break;
                }
                case 'a': {
                    switch (mode[1]) {
                        case '+': {
                            oflags = O_RDWR | O_CREAT | O_APPEND;
                            break;
                        }
                        default: {
                            puts("Unknown mode");
                            return NULL;
                        }
                    }
                    break;
                }
                default: {
                    puts("Unknown mode");
                    return NULL;
                }
            }
            break;
        }
        default: {
            puts("Unknown mode");
            return NULL;
        }
    }
    ret->fd = open(path, oflags, 0666);
    if (ret->fd == -1) {
        perror("open");
        return NULL;
    }
    return (FILE*)ret;
}

int fputs(FILE* fp, char* s) {
    FILE_PTR f = (FILE_PTR)fp;
    return write(f->fd, s, strlen(s));
}

int fputc(FILE* fp, int ch) {
    FILE_PTR f = (FILE_PTR)fp;
    return write(f->fd, &ch, 1);
}

int fgets(FILE* fp, char* buf, int n) {
    FILE_PTR f = (FILE_PTR)fp;
    return read(f->fd, buf, n);
}

int fclose(FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    return close(f->fd);
}
