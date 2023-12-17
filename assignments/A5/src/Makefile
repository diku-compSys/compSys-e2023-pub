# GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11 
GCC=gcc -g -Wall -Wextra -pedantic -std=gnu11 -O

all: sim
rebuild: clean all

# sim uses simulate
sim: *.c 
	$(GCC) *.c -o sim 

zip: ../src.zip

../src.zip: clean
	cd .. && zip -r src.zip src/Makefile src/*.c src/*.h

clean:
	rm -rf *.o sim  vgcore*
