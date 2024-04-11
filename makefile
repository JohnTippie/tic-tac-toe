CFLAGS=-std=c++17 -Wall -Werror -Wextra
LIBS=-lmingw32
SOURCES=main.cpp

all: 
	g++ $(SOURCES) -o tic-tac-toe $(CFLAGS) -L$(LIBS)