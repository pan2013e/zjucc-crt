#include "stdio.h"

int puts(char* s) {
    char* p = s;
    while (*p != '\0') {
        putchar(*p++);
    }
    putchar('\n');
    return 0;
}

int puti(int n) {
    char s[25] = { 0 };
    int pos = 0, num = n;
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
    putchar('\n');
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