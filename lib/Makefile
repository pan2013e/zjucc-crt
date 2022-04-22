OBJ = $(patsubst %.c,%.o, $(wildcard *.c))
SRC = $(wildcard *.c)
INC = ../include

all: ${OBJ}

%.o:%.c
	@$(CC) -c $< -o $@ -I${INC} -fno-builtin -nostartfiles -nostdlib -nostdinc
	@echo CC $<

clean:
	rm -f *.o *.out