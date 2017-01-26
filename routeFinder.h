#ifndef ROUTEFINDER_H
#define ROUTEFINDER_H
#include "maze.h"
#include <string>

class RouteFinder {
protected:
	Maze* maze;
public:
	RouteFinder(Maze* mazeIn);

	/*Requires:N/A
 	 *Effects:runs navigation on maze
 	 *Modifies:N/A*/
	virtual void navigate() =0;

	/*Requires:N/A
 	 *Effects:visually displays route taken to get to goal
 	 *Modifies:N/A*/
	virtual void display() =0;
};


class RandomRoute : public RouteFinder {
	unsigned int i;
	unsigned int j;
	int seed;
	std::string route;
public:
	RandomRoute(Maze* mazeIn, int seedIn);
	void display();
	void navigate();
};

#endif