CC = gcc
AS = as
AR = ar
LD = ld
LIBC_DIR = libc.a
arch = x86_64-linux-gnu
ARCH_DIR = ./lib/arch/${arch}
SRC_DIR = $(wildcard ${ARCH_DIR}/*.S) $(wildcard ${ARCH_DIR}/*.c)
OBJ_DIR = $(patsubst %.c,%.o,$(wildcard ./lib/*.c)) $(patsubst %.S,%.o,$(wildcard ${ARCH_DIR}/*.S)) $(patsubst %.c,%.o,$(wildcard ${ARCH_DIR}/*.c))
TEST_SRC_DIR = $(wildcard ./test/*.c)

.PHONY: clean test

all: ${SRC_DIR}
	@${MAKE} -C ${ARCH_DIR} all
	@${MAKE} -C lib all
	@${AR} cr ${LIBC_DIR} ${OBJ_DIR}
	@echo AR ${LIBC_DIR}

test: all ${TEST_SRC_DIR}
	@${MAKE} -C test all

clean: 
	rm -f ${LIBC_DIR}
	@${MAKE} -C ${ARCH_DIR} clean
	@${MAKE} -C test clean
