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
make  # default: x86_64-linux-gnu
# or
make -e arch=${ARCH_NAME}

# Use gcc or other C compilers
gcc -nostdlib -c ${FILE_NAME}.c
ld ${FILE_NAME}.o -L. -lc -o ${EXE_NAME}
./${EXE_NAME}

# Try test cases
make clean && make test
```

## Current supported platforms
* `x86_64-linux-gnu`

## Current supported functions
```c
/* C program entry */
void _start(); 

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
