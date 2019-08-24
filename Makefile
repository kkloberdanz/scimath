CFLAGS=-std=iso9899:1990
WARN_FLAGS=-Wall -Wextra -Wpedantic -Werror
CLANG=clang -Wassign-enum -Wenum-conversion
GCC=gcc
SANITIZE=-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined

OBJS=scimath.so

release: OPTIM_FLAGS=-Ofast -g -march=native -mtune=native
release: test

debug: OPTIM_FLAGS=-Og -ggdb -DDEBUG $(SANITIZE)
debug: test

valgrind: OPTIM_FLAGS=-Og -ggdb -DDEBUG
valgrind: test

COMPILER=$(GCC)

CC=$(COMPILER) $(OPTIM_FLAGS) $(CFLAGS) $(WARN_FLAGS)

loc: clean
	find . -path '*/.*' -prune -o -type f -exec sloccount {} \+

test: libscimath.so
	$(CC) -L . test.c -o test libscimath.so -lm -fopenmp
	./test

libscimath.so:
	$(CC) -c -fpic scimath.c -fopenmp -o scimath.o
	$(CC) -shared -o libscimath.so scimath.o

clean:
	rm -f *.o
	rm -f *.so
	rm -f test
