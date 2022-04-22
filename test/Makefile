EXE = $(patsubst %.c,%.out, $(wildcard *.c))
OBJ = $(patsubst %.c,%.o, $(wildcard *.c))
SRC = $(wildcard *.c)
INC = ../include
LDIR = ..

all: ${EXE}

%.out:%.o
	@${LD} $< -o $@ -L${LDIR} -lc

%.o:%.c
	@${CC} -c $< -I${INC} -fno-builtin -nostartfiles -nostdlib -nostdinc
	@echo CC $<

clean:
	rm -f *.o *.out