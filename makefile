CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic -fopenmp

all: main

main: main.o pgm.o pgm.h mandelbrot.o mandelbrot.h
	${CC} ${CFLAGS} main.o pgm.o mandelbrot.o -o $@ -lm

%.o: %.c pgm.h mandelbrot.h
	${CC} ${CFLAGS} -c $^ -lm

.PHONY: clean main

clean:
	rm -rf *.o
	rm -rf *.pgm
	rm -rf *.gch
