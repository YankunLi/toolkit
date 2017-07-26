CC = g++
CFLAGS = -g

TARGET = variant_visitor variant_get variant_RTTI variant_template

all: run1 run2 run3 run4

OBJS_SRC = Dog.cpp Cat.cpp Animal.cpp variant_visitor.cpp

OBJS = Dog.o Cat.o Animal.o

run1: $(OBJS) variant_visitor.o
	$(CC) -o $@ $^

run2: $(OBJS) variant_get.o
	$(CC) -o $@ $^

run3: $(OBJS) variant_RTTI.o
	$(CC) -o $@ $^

run4: $(OBJS) variant_template.o
	$(CC) -o $@ $^

Dog.o Cat.o Animal.o: Dog.h Cat.h Animal.h
#	$(CC) -o $@ -c $<

#Cat.o: Cat.h
#$(CC) -o $@ -c $<

#Animal.o: Animal.h
#	$(CC) -o $@ -c $<

variant_visitor.o: variant_visitor.cpp
	$(CC) -o $@ -c $<

variant_get.o: variant_get.cpp
	$(CC) -o $@ -c $<

variant_RTTI.o: variant_RTTI.cpp
	$(CC) -o $@ -c $<

variant_template.o: variant_template.cpp
	$(CC) -o $@ -c $<

.PHONY: clean

clean:
	-$(RM) *.o run*
