CC = gcc

CFLAGS = -g

TARGET = run

all: run

run: main.o daemon.o
	$(CC) -o $@ $^

main.o: main.c
	$(CC) -o $@ -c $<

daemon.o: daemon.c
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	$(RM)  *.o run
