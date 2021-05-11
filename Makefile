SHELL = /bin/bash
CC=gcc
CFLAGS=-g -std=c11 -Wall -Werror
TARGET=program
.PHONY: clean
all: $(TARGET)

a2: ./src/a2.c 
	$(CC) $(CFLAGS) $^ -o $@ -fopenmp

seq2D: a2
	./$^ 1 1

seq3D: a2
	./$^ 2 1

par2D: a2
	./$^ 3 1
	./$^ 3 2
	./$^ 3 4
	./$^ 3 8

par3D: a2
	./$^ 4 1
	./$^ 4 2
	./$^ 4 4
	./$^ 4 8

clean:
	rm -f ./a2


