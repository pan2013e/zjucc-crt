A Tiny CRT (C Runtime) Library
---

This library is built as a module of another project [zjucc](https://https://github.com/bugsz/c-compiler)

# Author

Zhiyuan Pan, Zhejiang University

# Usage

From the project root folder, run

```bash
make  # default: x86_64-linux-gnu
# or
make -e arch=${ARCH_NAME}

# Use gcc or other C compilers
gcc -nostdlib -c ${FILE_NAME}.c
ld ${FILE_NAME}.o -L. -lc -o ${EXE_NAME}
./${EXE_NAME}
```

# Current supported platforms
* x86_64-linux-gnu

# Current supported functions
* int write(int _fd, const void* buf, size_t size);