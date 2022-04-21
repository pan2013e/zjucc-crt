#include "stdio.h"

int main() {
    write(STDOUT_FILENO, "test", 4);
}