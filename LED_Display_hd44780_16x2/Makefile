
CC=gcc
CFLAGS= -g -Wall  -I/opt/ucc/include
LDFLAGS= -L/opt/ucc/lib
LDLIBS= -lhd44780  -lpigpiod_if2  -pthread
all:led

led:led.o

clean:
	rm -f *.o*~ led led.o
run:
	  ./led
