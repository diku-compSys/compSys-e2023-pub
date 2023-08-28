CFLAGS=-g -fsanitize=address -Wall -Wextra -pedantic

all: showfile pointers arrays stack

showfile: showfile.c
	gcc showfile.c -o showfile $(CFLAGS)

pointers: pointers.c
	gcc pointers.c -o pointers $(CFLAGS)

arrays: arrays.c
	gcc arrays.c -o arrays $(CFLAGS)

stack: stack.c
	gcc stack.c -o stack $(CFLAGS)

clean:
	rm -f showfile pointers arrays
