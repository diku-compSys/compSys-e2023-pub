CFLAGS=-Wall -Wextra -pedantic
CC=gcc

all: test

test: fib.o test.o
	$(CC) test.o fib.o -o test $(CFLAGS)

fib.o: fib.c
	$(CC) -c fib.c $(CFLAGS)

test.o: test.c
	$(CC) -c test.c $(CFLAGS)

do_test: test
	./test

clean:
	rm -f fib.o test.o test
