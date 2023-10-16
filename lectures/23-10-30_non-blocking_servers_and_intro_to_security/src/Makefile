#GCC=gcc -O3 -g -Wall -Wextra -pedantic -std=gnu11
GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11
LD_FLAGS= -lpthread

all: exercise

rebuild: clean all

exercise: exercise.c exercise.h sha256.o compsys_helpers.o
	$(GCC) $< *.o -o $@ $(LD_FLAGS)

compsys_helpers.o : compsys_helpers.c compsys_helpers.h
	$(CC) $(CFLAGS) -c $< -o $@

sha256.o : sha256.c sha256.h
	$(CC) $(CFLAGS) -c $< -o $@

zip: ../src.zip

../src.zip: clean
	cd .. && zip -r src.zip src/Makefile src/*.c src/*.h

clean:
	rm -rf *.o exercise sha256 vgcore*
