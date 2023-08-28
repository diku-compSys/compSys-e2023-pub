CC=gcc
CFLAGS=-Wall -Wextra -pedantic -O3

all: locality

locality: locality.o
	$(CC) -o locality locality.o

locality.data: locality
	./locality > locality.data

mountain.png: locality.data mountain.gnuplot
	gnuplot mountain.gnuplot

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f locality locality.data mountain.png *.o
