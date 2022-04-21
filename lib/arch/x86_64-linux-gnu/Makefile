OBJ = $(patsubst %.S,%.o,$(wildcard *.S)) $(patsubst %.c,%.o,$(wildcard *.c))
SRC = $(wildcard *.S) $(wildcard *.c)
INC = ../../../include

.PHONY: all clean

all: ${OBJ}

%.o: %.c
	@$(CC) -nostdlib -c $< -o $@ -I${INC}
	@echo CC $<

%.o: %.S
	@$(AS) $< -o $@
	@echo AS $<

clean:
	rm -f *.o