# PA5_part1 Makefile #
# Group 10 #
# Name: Zhifeng Lin, Han Xiao #

CC = g++
CFLAGS = -g 

all: gatesim

gatesim: net.o gates.o design.o parse.o readsim.o gatesim.o 
	g++ -g -Wall -o gatesim net.o gates.o design.o parse.o readsim.o gatesim.o

net.o: net.h net.cpp
	$(CC) $(CFLAGS) -c net.cpp

gates.o: gates.h gates.cpp
	$(CC) $(CFLAGS) -c gates.cpp

design.o: design.h gates.h net.h design.cpp
	$(CC) $(CFLAGS) -c design.cpp
	
parse.o: parse.h design.h gates.h net.h parse.cpp
	$(CC) $(CFLAGS) -c parse.cpp
	
gatesim.o: parse.h design.h gates.h net.h gatesim.cpp
	$(CC) $(CFLAGS) -c gatesim.cpp
	
readsim.o: readsim.h readsim.cpp
	$(CC) $(CFLAGS) -c readsim.cpp
clean:
	rm -f *.o *~
