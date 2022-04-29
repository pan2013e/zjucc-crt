OBJ = $(patsubst %.c,%.o, $(wildcard *.c))
SRC = $(wildcard *.c)
INC = ../include

ifeq (${arch}, x86_64-linux-gnu)
    DEF = __X86_64__=1
else ifeq (${arch}, riscv64-linux-gnu)
    DEF = __RISCV_64__=1
else
	DEF = __UNKNOWN_ARCH__=1
endif

all: ${OBJ}

%.o:%.c
	@$(CC) -c $< -o $@ -I${INC} -fno-builtin -nostartfiles -nostdlib -nostdinc -D${DEF}
	@echo CC $<

clean:
	rm -f *.o *.out