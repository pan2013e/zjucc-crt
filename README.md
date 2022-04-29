A Tiny CRT (C Runtime) Library
---

## Introduction
* The library is a simplified implementation of a subset of `libc`, and it's for educational purposes
only.
* The library is a submodule of my C compiler project [zjucc](https://github.com/pan2013e/c-compiler). 

## Author

Zhiyuan Pan, Zhejiang University

[zy_pan@zju.edu.cn](mailto:zy_pan@zju.edu.cn)

## Usage

From the project root folder, run

```bash
make  # default arch: x86_64-linux-gnu
# or specify architecture by '-e' option
make -e arch=${ARCH_NAME} # for available archs, see next section

# Use gcc or other C compilers
# The compiler's C library is now unnecessary
gcc -c ${FILE_NAME}.c -fno-builtin -nostdinc -nostdlib -nostartfiles
ld ${FILE_NAME}.o -L. -lc -o ${EXE_NAME}
./${EXE_NAME}

# Try test cases
make clean && make test
```

## Current supported platforms
* `x86_64-linux-gnu`
* `riscv-linux-gnu` (still has bugs to deal with)

## Current supported functions
```c
/* unistd.h */
size_t write(int _fd, const void* buf, size_t size);

/* stdio.h */
int putchar(int ch);
int puts(char* s);
int puti(int n);
int getchar();
int gets(char* buf);

/* string.h */
void* memset(void *, int, unsigned long);
```
