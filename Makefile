CC=g++
CFLAGS=-g -Wall
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)

MAIN=main

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean

clean:
	$(RM) *.o *~ $(MAIN)
