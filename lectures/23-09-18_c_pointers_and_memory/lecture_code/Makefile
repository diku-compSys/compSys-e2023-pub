CFLAGS=-g -fsanitize=address -Wall -Wextra -pedantic

all: showfile pointers arrays stack demonstration

showfile: showfile.c
	gcc showfile.c -o showfile $(CFLAGS)

pointers: pointers.c
	gcc pointers.c -o pointers $(CFLAGS)

arrays: arrays.c
	gcc arrays.c -o arrays $(CFLAGS)

stack: stack.c
	gcc stack.c -o stack $(CFLAGS)

demonstration: demonstration.c
	gcc demonstration.c -o demonstration $(CFLAGS)

clean:
	rm -f showfile pointers arrays demonstration stack
