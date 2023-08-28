CC=gcc
CFLAGS=-Wall -Wextra -pedantic
PROGRAMS=hello exec0 exec1 fork0 fork1 fork2 fork2fd forkbomb pipe0 zombies forks

all: $(PROGRAMS)

%: %.c
	$(CC) -o $@ $^ $(CFLAGS)
