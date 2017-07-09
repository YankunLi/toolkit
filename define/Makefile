CC = g++
CFLAGS = -g

TARGET = run

all: run

OBJS_SRC = main.cpp

run: main.o config.o
	$(CC) -o $@ $^

main.o: main.cpp
	$(CC) -o $@ -c $^

config.o: config.cpp
	$(CC) -c $<

clean:
	$(RM)  *.o run

