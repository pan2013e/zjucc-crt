OBJ = $(patsubst %.S,%.o,$(wildcard *.S)) $(patsubst %.c,%.o,$(wildcard *.c))
SRC = $(wildcard *.S) $(wildcard *.c)
INC = ../../../include

.PHONY: all clean

all: ${OBJ}

%.o: %.c
	@$(CC) -c $< -o $@ -I${INC} -fno-builtin -nostartfiles -nostdlib -nostdinc -D__RISCV_64__=1
	@echo CC $<

%.o: %.S
	@$(AS) $< -o $@
	@echo AS $<

clean:
	rm -f *.o