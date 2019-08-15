CFLAGS=-std=iso9899:1990
WARN_FLAGS=-Wall -Wextra -Wpedantic -Werror
CLANG=clang -Wassign-enum -Wenum-conversion
SANITIZE=-fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined

OBJS=scimath.so

release: OPTIM_FLAGS=-O2
release: test

debug: OPTIM_FLAGS=-Og -ggdb -DDEBUG $(SANITIZE)
debug: test

valgrind: OPTIM_FLAGS=-Og -ggdb -DDEBUG
valgrind: test

CC=cc $(OPTIM_FLAGS) $(CFLAGS) $(WARN_FLAGS)

loc: clean
	find . -path '*/.*' -prune -o -type f -exec sloccount {} \+

test: scimath.so
	$(CC) -L . test.c -o test scimath.so -lm -fopenmp
	./test

scimath.so:
	$(CC) -c -fpic scimath.c -lm -fopenmp -o scimath.o
	$(CC) -shared -o scimath.so scimath.o

clean:
	rm -f scimath.o
	rm -f scimath.so
