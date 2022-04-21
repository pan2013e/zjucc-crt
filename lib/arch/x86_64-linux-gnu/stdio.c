#include "stdio.h"

int putchar(int ch) {
    int s[2] = { ch, '\0' };
    return write(1, s, 1);
}