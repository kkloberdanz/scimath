###############################################################################
# Copyright 2019 Kyle Kloberdanz
###############################################################################

CFLAGS=-std=c89 -fopenmp -fpic
WARN_FLAGS=-Wall -Wextra -Wpedantic -Werror
CLANG=clang \
	  -Wassign-enum \
	  -Wenum-conversion \
	  -Weverything \
	  -Wno-missing-prototypes
GCC=gcc
AR=ar rcs
SANITIZE=-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined

OBJS=scimath.so

release: OPTIM_FLAGS=-Ofast -g -march=native -mtune=native
release: all

debug: OPTIM_FLAGS=-O0 -ggdb -DDEBUG $(SANITIZE)
debug: all

valgrind: OPTIM_FLAGS=-O0 -ggdb -DDEBUG
valgrind: all

COMPILER=$(GCC)

CC=$(COMPILER) $(OPTIM_FLAGS) $(CFLAGS) $(WARN_FLAGS)

.PHONY: all
all: libscimath.so libscimathstatic.a

.PHONY: loc
loc: clean
	find . -path '*/.*' -prune -o -type f -exec sloccount {} \+

template: template.h template.c
	$(CC) -c template.c

simd.o: simd.c simd.h
	$(CC) -c simd.c

scimath.o: scimath.c scimath.h
	$(CC) -c scimath.c

libscimath.so: scimath.o simd.o
	$(CC) -shared -o libscimath.so scimath.o -lm -fopenmp

libscimathstatic.a: scimath.o simd.o
	$(AR) libscimathstatic.a scimath.o simd.o

.PHONY: clean
clean:
	rm -f *.o
	rm -f *.so
	rm -f *.a
