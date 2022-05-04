#include "errno.h"

static int __errno;

int* __errno_location() {
    return &__errno;
}