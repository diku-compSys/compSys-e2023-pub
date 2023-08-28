CFLAGS=-Wall -Wextra -pedantic

all: 1darray sumrows

clean:
	rm -f mem args

%: %.c
	gcc -o $@ $(CFLAGS) $^
