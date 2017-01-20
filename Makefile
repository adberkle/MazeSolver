CC = g++
CFLAGS = -g -Wall

HDRS = maze.h routefinder.h
SRCS = main.cpp maze.cpp
OBJS = $(SRCS:.cpp=.o)

all:
	$(CC) $(CFLAGS) $(SRCS) -o maze.o

run:
	rm -f -r $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o maze.o
	./maze.o

.PHONY: clean
clean: 
	rm -f -r $(OBJS)