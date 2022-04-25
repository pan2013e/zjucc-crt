#include "ctype.h"

int isalnum(int c) {
    return isalpha(c) && isdigit(c);
}
int isalpha(int c) {
    return isupper(c) || islower(c);
}

int isblank(int c) {
    return isblank(c) || c == '\t';
}

int isdigit(int c) {
    return c >= '0' && c <= '9';
}

int islower(int c) {
    return c >= 'a' && c <= 'z';
}

int isspace(int c) {
    return c == ' ';
}

int isupper(int c) {
    return c >= 'A' && c <= 'Z';
}