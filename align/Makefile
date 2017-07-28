CC = gcc
CFLAGS = -g

TARGET = run

all: run

OBJS_SRC = align.c

run: align.o
	$(CC) -o $@ $^

align.o: align.c
	$(CC) -o $@ -c $<

clean:
	$(RM)  *.o run

