CC = g++
CFLAGS = -g

TARGET = run

all: run

OBJS_SRC = Dog.cpp Cat.cpp Animal.cpp variant_visitor.cpp

run: Dog.o Cat.o Animal.o variant_visitor.o
	$(CC) -o $@ $^

Dog.o: Dog.cpp
	$(CC) -o $@ -c $<

Cat.o: Cat.cpp
	$(CC) -o $@ -c $<

Animal.o: Animal.cpp
	$(CC) -o $@ -c $<

variant_visitor.o: variant_visitor.cpp
	$(CC) -o $@ -c $<

clean:
	$(RM) *.o run
