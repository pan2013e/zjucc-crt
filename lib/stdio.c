#include "string.h"
#include "errno.h"
#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "stdlib.h"

static int fputi(int n, FILE* fp);
static int fputf(double x, FILE* fp);

struct __IO_vtable {
    FILE* fp;
    int (*fputc)(int, FILE*);
    int (*fgetc)(FILE*);
    int (*fputs)(char*, FILE*);
    int (*fputi)(int, FILE*);
    int (*fputf)(double, FILE*);
};

typedef struct __IO_FILE* FILE_PTR;
struct __IO_FILE {
    int fd;
    int oflags;
    int offset;
    struct __IO_vtable vtable;
};

struct __IO_FILE stdin_io = {
    0, O_RDONLY, 0, { &stdin_io, fputc, fgetc, fputs, fputi, fputf }
};
struct __IO_FILE stdout_io = {
    1, O_WRONLY, 0, { &stdout_io, fputc, fgetc, fputs, fputi, fputf }
};
struct __IO_FILE stderr_io = {
    2, O_WRONLY, 0, { &stderr_io, fputc, fgetc, fputs, fputi, fputf }
};

FILE* stdin = &stdin_io;
FILE* stdout = &stdout_io;
FILE* stderr = &stderr_io;

int puts(char* s) {
    char* p = s;
    while (*p != '\0') {
        putchar(*p++);
    }
    putchar('\n');
    return 0;
}

int fputi(int n, FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    char s[__INT_WIDTH__] = { 0 };
    int pos = 0;
    long num = n;
    if (n < 0) {
        f->vtable.fputc('-', f->vtable.fp);
        num = -num;
    }
    do {
        s[pos++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);
    for (int i = pos;i >= 0;i--) {
        f->vtable.fputc(s[i], f->vtable.fp);
    }
    return 0;
}

int fputf(double x, FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    int precision = 6, bias = 1e6;
    if (x < 0) {
        f->vtable.fputc('-', f->vtable.fp);
        x = -x;
    }
    long temp = (long)(x * bias);
    if (temp != 0) {
        fputi(x, f->vtable.fp);
        fputc('.', f->vtable.fp);
        fputi(temp % bias, f->vtable.fp);
    } else {
        fputi(0, f->vtable.fp);
    }
    return 0;
}

char* gets(char* buf) {
    char ch;
    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            *buf = '\0';
            return NULL;
        }
        *buf++ = ch;
    }
    *buf = '\0';
    return buf;
}

int vfprintf(FILE* fp, char* fmt, __builtin_va_list ap) {
    FILE_PTR f = (FILE_PTR)fp;
    char ch;
    while (ch = *fmt++) {
        if (ch != '%') {
            f->vtable.fputc(ch, f->vtable.fp);
        } else {
            if (*fmt == '*') {
                int n_spaces = __builtin_va_arg(ap, int);
                for (int i = 0;i < n_spaces;i++) {
                    f->vtable.fputc(' ', f->vtable.fp);
                }
                fmt++;
            }
            switch (*fmt) {
                case 'c': {
                    int _ch = __builtin_va_arg(ap, int);
                    f->vtable.fputc(_ch, f->vtable.fp);
                    fmt++;
                    break;
                }
                case 's': {
                    char* s = __builtin_va_arg(ap, char*);
                    f->vtable.fputs(s, f->vtable.fp);
                    fmt++;
                    break;
                }
                case 'd': {
                    int n = __builtin_va_arg(ap, int);
                    f->vtable.fputi(n, f->vtable.fp);
                    fmt++;
                    break;
                }
                case 'f': {
                    double x = __builtin_va_arg(ap, double);
                    f->vtable.fputf(x, f->vtable.fp);
                    fmt++;
                    break;
                }
                case '%': {
                    f->vtable.fputc('%', f->vtable.fp);
                    fmt++;
                    break;
                }
                default: {
                    stderr_io.vtable.fputs("Unknown format specifier\n", stderr_io.vtable.fp);
                    fmt++;
                    break;
                }
            }
        }
    }
    return 0;
}

int printf(char* fmt, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    vfprintf(stdout, fmt, ap);
    __builtin_va_end(ap);
    return 0;
}

int fprintf(FILE* fp, char* fmt, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    vfprintf(fp, fmt, ap);
    __builtin_va_end(ap);
    return 0;
}

int vfscanf(FILE* fp, char* fmt, ...) {
    
}

int scanf(char* fmt, ...) {
    __builtin_va_list ap;
    __builtin_va_start(ap, fmt);
    vfscanf(stdin, fmt, ap);
    __builtin_va_end(ap);
    return 0;
}

void perror(char* s) {
    printf("%s: %s\n", s, strerror(errno));
}

int mode_to_oflags(char* mode) {
    int oflags = 0;
    if (strchr(mode, 'r') != NULL) {
        oflags |= O_RDONLY;
    }
    if (strchr(mode, 'w') != NULL) {
        oflags |= O_WRONLY;
    }
    if (strchr(mode, 'a') != NULL) {
        oflags |= O_APPEND;
    }
    if (strchr(mode, '+') != NULL) {
        oflags |= O_CREAT;
    } else {
        oflags |= O_TRUNC;
    }
    return oflags;
}


FILE* fopen(char* path, char* mode) {
    FILE_PTR ret = (FILE_PTR)malloc(sizeof(struct __IO_FILE));
    if (ret == NULL) {
        return NULL;
    }
    int oflags = mode_to_oflags(mode);
    ret->fd = open(path, oflags, 0666);
    ret->offset = 0;
    ret->oflags = oflags;
    struct __IO_vtable new_table = { (FILE*)ret, fputc, fgetc, fputs, fputi, fputf };
    ret->vtable = new_table;
    if (ret->fd < 0) {
        return NULL;
    }
    return (FILE*)ret;
}

int fputs(char* s, FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    return write(f->fd, s, strlen(s));
}

int fputc(int ch, FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    return write(f->fd, &ch, 1);
}

int fgetc(FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    char ch;
    int ret = read(f->fd, &ch, 1);
    if (ret == 1) {
        return ch;
    } else {
        return EOF;
    }
}

int feof(FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    return lseek(f->fd, 0, SEEK_CUR) == lseek(f->fd, 0, SEEK_END);
}

char* fgets(char* buf, int n, FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    for (int i = 0;i < n;i++) {
        int ch = read(f->fd, buf + i, 1);
        if (ch < 0) {
            return NULL;
        }
        if (buf[i] == '\n' || ch == 0) {
            buf[i] = '\0';
            return buf;
        }
    }
    buf[n] = '\0';
    return NULL;
}

int fclose(FILE* fp) {
    FILE_PTR f = (FILE_PTR)fp;
    return close(f->fd);
}

int fileno(FILE* fp) {
    return ((FILE_PTR)fp)->fd;
}