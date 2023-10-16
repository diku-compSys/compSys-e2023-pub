CC=gcc
CFLAGS=-pthread
PROGRAMS=stdin_to_stdout echoclient echoserver short_count_client short_count_server robust_server robust_client

all: $(PROGRAMS)

compsys_helpers.o : compsys_helpers.c compsys_helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

%: %.c compsys_helpers.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(PROGRAMS)
