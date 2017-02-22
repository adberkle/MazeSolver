#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H
#include "maze.h"
#include <string>

class RouteFinder {
protected:
	Maze* maze;
	std::string route;
public:
	RouteFinder(Maze* mazeIn);
	virtual ~RouteFinder(){};

	/*Requires:N/A
 	 *Effects:runs navigation on maze
 	 *Modifies:route string*/
	virtual void navigate() =0;

	/*Requires:N/A
 	 *Effects:visually displays route taken to get to goal
 	 *Modifies:N/A*/
	void display();

	/*Requires:navigate() must have been run first
 	 *Effects:verifies the route used leads to the exit
 	 *Modifies:N/A*/
	bool verify();
};


class RandomRoute : public RouteFinder {
	unsigned int i;
	unsigned int j;
	int seed;
public:
	RandomRoute(Maze* mazeIn, int seedIn);
	~RandomRoute();

	void navigate();
};

class DepthFirst : public RouteFinder {
	struct Node{
		unsigned int parent;
		unsigned int i;
		unsigned int j;
		Node(unsigned int x, unsigned int y, unsigned int parentIndex);
	};
	
public:
	DepthFirst(Maze* mazeIn);
	~DepthFirst();
	void navigate();
};

#endif