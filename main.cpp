#include "maze.h"			//maze generating data structures
#include "routeFinder.h"    //route finding data structures
#include <stdio.h>
#include <unistd.h>			//getopt
#include <cstdlib>			//atoi
#include <iostream>

/*Requires:
 *Effects:
 *Modifies:*/
int main(int argc, char *argv[]) {
	//default parameters
	unsigned int height = 5;
	unsigned int width = 5;
	unsigned int seed = 500;
	int algorithm = 1;

	//get input from command line;
	int c;
	opterr = 0;
	while ((c = getopt (argc, argv, "a:h:s:w:")) != -1)
		switch (c) {
		case 'h':
			height = atoi(optarg);
			break;
		case 'w':
			width = atoi(optarg);
			break;
		case 'a':
			algorithm = atoi(optarg);
			break;
		case 's':
			seed = atoi(optarg);
			break;
		case '?':
			if (optopt == 's' || optopt == 'a' || optopt == 'h' || optopt == 'w')
		      fprintf (stderr, "Option -%c requires an argument.\n", optopt);
		    else if (isprint (optopt))
		      fprintf (stderr, "Unknown option `-%c'.\n", optopt);
		    else
		      fprintf (stderr,
		               "Unknown option character `\\x%x'.\n",
		               optopt);
		    return 1;
		default:
			break;
	}

	//make maze based on command line arguments
	RPrims maze(height, width, seed);
	//maze.display();

	//make routefinder data structure based on command line arguments
	RouteFinder* routeFinder;
	switch(algorithm){
		case 0:
			routeFinder = new RouteFinder();
		case 1:
			routeFinder = new DepthFirst(&maze);
		case 3:
			routeFinder = new RandomRoute(&maze, seed);
		default:
			routeFinder = new DepthFirst(&maze);
	}

	//run route finding
	routeFinder->navigate();
	//routeFinder->display();
	std::cout << routeFinder->verify() << std::endl;

	delete routeFinder;
	return 0;
}