CFLAGS=-g -Wall
all: fibonacci
fibonacci.s: fibonacci.c
	gcc -S $(CFLAGS) fibonacci.c
fibonacci.o: fibonacci.s
	gcc -c $(CFLAGS) fibonacci.s
fibonacci: fibonacci.o
	gcc -o fibonacci fibonacci.o
clean: 
	rm -f *~ fibonacci.s fibonacci.o fibonacci
run: 
	./fibonacci 

