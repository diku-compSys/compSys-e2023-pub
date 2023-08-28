CC=gcc
CFLAGS=-Wall -Wextra -pedantic -pthread -O3
PROGRAMS=sumbytes-one sumbytes-two sumbytes-many

all: $(PROGRAMS)

%: %.c
	$(CC) -o $@ $^ $(CFLAGS)

%_bytes:
	dd if=/dev/urandom of=$@ bs=$* count=1

clean:
	rm -f $(PROGRAMS) *_bytes
