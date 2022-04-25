#include "time.h"

static int __rand_initialized = 0;
static int r[1000];
static int t = 0;
static unsigned int seed = 0;

void srand(long s) {
    seed = s % 32767;
}

long rand() {
    int i;
    if (__rand_initialized == 0) {
        r[0] = seed;
        for (i = 1; i < 31; i++) {
            r[i] = (16807LL * r[i - 1]) % 2147483647;
            if (r[i] < 0) {
                r[i] += 2147483647;
            }
        }
        for (i = 31; i < 34; i++) {
            r[i] = r[i - 31];
        }
        for (i = 34; i < 344; i++) {
            r[i] = r[i - 31] + r[i - 3];
        }
		__rand_initialized = 1;
    }
	t = t % 656;
    r[t + 344] = r[t + 344 - 31] + r[t + 344 - 3];
    t++;
    return (long)r[t - 1 + 344] % 10 + 1;
}
