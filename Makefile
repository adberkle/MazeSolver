CC = g++
CFLAGS = -Wall -std=c++11
PFLAGS = -lprofiler -fno-omit-frame-pointer --enable-frame-pointers -Wl,--eh-frame-hdr

HDRS = maze.h routefinder.h
SRCS = main.cpp maze.cpp routeFinder.cpp
OBJS = $(SRCS:.cpp=.o) $(SRCS:.cpp=.o.dSYM)

all:
	$(CC) $(CFLAGS) $(SRCS) -o maze.o

run:
	rm -f -r $(OBJS)
	$(CC) -g $(CFLAGS) $(SRCS) -o maze.o
	./maze.o -h 5 -w 5 -s 500 -a 1

gdb:
	rm -f -r $(OBJS)
	$(CC) -g $(CFLAGS) $(SRCS) -o maze.o
	sudo gdb maze.o

time:
	$(CC) -lprofiler $(CFLAGS) $(SRCS) -o maze.o

.PHONY: clean
clean: 
	rm -f -r $(OBJS)
