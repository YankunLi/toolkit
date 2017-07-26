CC = g++
CFLAGS = -g

TARGET = run

all: run

OBJS_SRC = Dog.cpp Cat.cpp Animal.cpp variant_visitor.cpp

OBJS = Dog.o Cat.o Animal.o variant_visitor.o

run: $(OBJS)
	$(CC) -o $@ $^

Dog.o Cat.o : Dog.h Cat.h
#	$(CC) -o $@ -c $<

#Cat.o: Cat.h
#$(CC) -o $@ -c $<

Animal.o: Animal.h
#	$(CC) -o $@ -c $<

variant_visitor.o: variant_visitor.cpp
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	-$(RM) *.o run
