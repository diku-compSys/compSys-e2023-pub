CC=gcc
CFLAGS=-g -pedantic -std=c99 -Wall -Wextra

calc: calc.o stack.o
	$(CC) $(CFLAGS) calc.o stack.o -o calc

calc.o: calc.c stack.h
	$(CC) $(CFLAGS) -c calc.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

clean:
	rm -f *o
	rm -f calc

all: calc
