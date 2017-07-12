CC = gcc
CFLAGS = -g

TARGET = run

all: run

run: resize.o file.o
	$(CC) -o $@ $^

resize.o: resize.c
	$(CC) -o $@ -c $^

file.o: file.c
	$(CC) -c $<

clean:
	$(RM)  *.o run test_file

