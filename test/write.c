#include "stdio.h"
#include "stdlib.h"
#include "setjmp.h"

void exit_print() {
    printf("Bye\n");
}

jmp_buf env;

void test() {
    printf("In function test...\n");
    longjmp(env, 88);
    printf("Dead code...\n");
}

int main() {
    atexit(exit_print);
    int ret = setjmp(env);
    if (ret == 0) {
        printf("set jump success, ret = %d\n", ret);
        test();
    } else {
        printf("long jump here, ret = %d\n", ret);
    }
}