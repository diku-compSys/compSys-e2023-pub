CC = gcc
CFLAGS =-Wall -Wextra -pedantic -std=gnu11
LD_FLAGS = -lpthread

all : conversion

rebuild : clean all

conversion : conversion.c
	$(CC) $(CFLAGS) $< -o $@ $(LD_FLAGS)

clean :
	rm -rf *.o conversion
