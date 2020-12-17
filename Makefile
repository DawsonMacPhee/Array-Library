CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: array.o

array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c -o array.o

clean:
	rm array.o