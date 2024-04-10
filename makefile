CFLAGS=-std=c17
LIBS=-lmingw32
SOURCES=main.c

all: 
	gcc $(SOURCES) -o tic-tac-toe $(CFLAGS) -L$(LIBS)