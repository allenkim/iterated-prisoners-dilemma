CC=g++
CFLAGS=-g -Wall -std=c++11
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

MAIN=main

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean

clean:
	$(RM) *.o *~ $(MAIN)
