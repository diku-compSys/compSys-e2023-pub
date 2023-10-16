#GCC=gcc -O3 -g -Wall -Wextra -pedantic -std=gnu11
GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread

all: exercise

rebuild: clean all

exercise: exercise.c exercise.h
	$(GCC) $< -o $@ $(LD_FLAGS)
zip: ../src.zip

../src.zip: clean
	cd .. && zip -r src.zip src/Makefile src/*.c src/*.h

clean:
	rm -rf *.o exercise vgcore*
