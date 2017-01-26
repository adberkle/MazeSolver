CC = g++
CFLAGS = -g -Wall

HDRS = maze.h routefinder.h
SRCS = main.cpp maze.cpp routeFinder.cpp
OBJS = $(SRCS:.cpp=.o) $(SRCS:.cpp=.o.dSYM)

all:
	$(CC) $(CFLAGS) $(SRCS) -o maze.o

run:
	rm -f -r $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o maze.o
	./maze.o

gdb:
	rm -f -r $(OBJS)
	$(CC) -g $(CFLAGS) $(SRCS) -o maze.o
	sudo gdb maze.o

.PHONY: clean
clean: 
	rm -f -r $(OBJS)