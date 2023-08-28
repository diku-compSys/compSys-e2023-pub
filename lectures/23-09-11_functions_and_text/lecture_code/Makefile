CFLAGS=-Wall -Wextra -pedantic

all: mem args printf fwrite-simple fwrite-hpps fwrite-int fread-bytes

clean:
	rm -f mem args

mem: mem.c
	gcc -o mem $(CFLAGS) mem.c

args: args.c
	gcc -o args $(CFLAGS) args.c

%: %.c
	gcc -o $@ $(CFLAGS) $^
