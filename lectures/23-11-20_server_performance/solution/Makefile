#GCC=gcc -O3 -g -Wall -Wextra -pedantic -std=gnu11
GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread

all: exercise p2p

rebuild: clean all

csapp.o: csapp.c csapp.h
	$(GCC) -c $< -o $@

exercise: exercise.c exercise.h csapp.o
	$(GCC) $< *.o -o $@ $(LD_FLAGS)

p2p: p2p.c csapp.o
	$(GCC) $< *.o -o $@ $(LD_FLAGS)

zip: ../src.zip

../src.zip: clean
	cd .. && zip -r src.zip src/Makefile src/*.c src/*.h

clean:
	rm -rf *.o exercise vgcore* p2p
