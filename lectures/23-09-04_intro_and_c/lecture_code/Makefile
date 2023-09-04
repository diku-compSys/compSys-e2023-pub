CFLAGS=-Wall -Wextra -pedantic -std=c11

all: helloworld error args sum roll side_one side_two

helloworld: helloworld.c
	gcc helloworld.c -o helloworld $(CFLAGS)

error: error.c
	gcc error.c -o error $(CFLAGS)

args: args.c
	gcc args.c -o args $(CFLAGS)

sum: sum.c
	gcc sum.c -o sum $(CFLAGS)

roll: roll.c
	gcc roll.c -o roll $(CFLAGS)

side_one: side_one.c
	gcc side_one.c -o side_one $(CFLAGS)

side_two: side_two.c
	gcc side_two.c -o side_two $(CFLAGS)

clean:
	rm -f helloworld error args sum roll side_one side_two
