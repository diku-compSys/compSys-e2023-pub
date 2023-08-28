CC=gcc
CFLAGS=-O3 -Wall -Wextra -pedantic

all: plot.png

plot.png: ijk.runtimes kij.runtimes jki.runtimes plot.gnuplot
	gnuplot plot.gnuplot

matmul: matmul.c
	$(CC) -o matmul matmul.c $(CFLAGS)

ijk.runtimes: matmul
	./matmul ijk > ijk.runtimes

kij.runtimes: matmul
	./matmul kij > kij.runtimes

jki.runtimes: matmul
	./matmul jki > jki.runtimes

clean:
	rm -f matmul plotlpng *.runtimes
