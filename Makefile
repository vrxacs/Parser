CC = g++
CFLAGS = -Wall -pedantic 

all: Parser.out

Parser.out: Parser.cpp
	$(CC) $(CFLAGS) Parser.cpp