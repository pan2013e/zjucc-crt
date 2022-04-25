#include "stdio.h"

int puts(char* s) {
    char* p = s;
    while (*p != '\0') {
        putchar(*p++);
    }
    return 0;
}

int puti(long n) {
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
    int precision = 6, bias = 1e6, mod = 1e7;
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    long temp = (long)(x * bias);
    if (temp != 0) {
        puti(x);
        putchar('.');
        puti(temp % mod);
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