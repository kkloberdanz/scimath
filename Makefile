###############################################################################
# Copyright 2019 Kyle Kloberdanz
###############################################################################

CFLAGS=-std=iso9899:1990
WARN_FLAGS=-Wall -Wextra -Wpedantic -Werror
CLANG=clang -Wassign-enum -Wenum-conversion -Weverything -Wno-missing-prototypes
GCC=gcc
SANITIZE=-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined

OBJS=scimath.so

release: OPTIM_FLAGS=-Ofast -g -march=native -mtune=native
release: run

debug: OPTIM_FLAGS=-O0 -ggdb -DDEBUG $(SANITIZE)
debug: run

valgrind: OPTIM_FLAGS=-O0 -ggdb -DDEBUG
valgrind: run

COMPILER=$(CLANG)

CC=$(COMPILER) $(OPTIM_FLAGS) $(CFLAGS) $(WARN_FLAGS)

loc: clean
	find . -path '*/.*' -prune -o -type f -exec sloccount {} \+

run: test
	./test

test: libscimath.so template
	$(CC) -L . test.c template.o -o test -lscimath -lm -fopenmp

template: template.h template.c
	$(CC) -c template.c

libscimath.so:
	$(CC) -c -fpic scimath.c -fopenmp -o scimath.o
	$(CC) -shared -o libscimath.so scimath.o

clean:
	rm -f *.o
	rm -f *.so
	rm -f test
