CC=gcc
CFLAGS=-Wall -Wextra -pedantic
PROGRAMS=mallocs small_mallocs mmap_fork mmap_shared

all: $(PROGRAMS)

%: %.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(PROGRAMS)
