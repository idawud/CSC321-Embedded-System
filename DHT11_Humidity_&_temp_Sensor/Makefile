CC=gcc
CFLAGS= -g -I/opt/ucc/include -Wall 
LDLIBS=-lwiringPi -ldht11
LDFLAGS=-L/opt/ucc/lib

all:myprog
myprog: myprog.c
	gcc -o myprog $(CFLAGS) $(LDFLAGS) myprog.c $(LDLIBS)


clean:
	rm -f *~ myprog 
