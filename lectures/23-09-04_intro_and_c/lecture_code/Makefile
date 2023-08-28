CFLAGS=-Wall -Wextra -pedantic -std=c11

all: helloworld error args sum roll

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

clean:
	rm -f helloworld error args sum roll
