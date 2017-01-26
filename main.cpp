#include "maze.h"			//maze generating data structures
#include "routeFinder.h"    //route finding data structures


/*Requires:
 *Effects:
 *Modifies:*/

int main(int argc, char *argv[]) {
	RPrims maze(20,20,500);
	maze.show();
	RandomRoute rand(&maze, 500);
	rand.navigate();
	rand.display();
}