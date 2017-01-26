#include "routeFinder.h"
#include "iostream"
#include <random>

RouteFinder::RouteFinder(Maze* mazeIn):maze(mazeIn){}

RandomRoute::RandomRoute(Maze* mazeIn, int seedIn):RouteFinder(mazeIn),i(0u),
	j(0u),seed(seedIn),route(""){}

/*Requires:N/A
 *Effects:visually displays route taken to get to goal
 *Modifies:N/A*/
void RandomRoute::display(){
	 std::cout << route << std::endl;
}

/*Requires:N/A
 *Effects:runs navigation on maze
 *Modifies:N/A*/
void RandomRoute::navigate(){
	int direction;
	std::mt19937_64 ranNum(seed);
	while(j != maze->height - 1 && i != maze->width - 1){
		direction = ranNum() % 4;
		switch(direction) {
			case 0:
				if(!maze->isWall(i+1, j)){
					i++;
					route +='r';
				}
				break;
			case 1:
				if(!maze->isWall(i-1, j)){
					i--;
					route +='l';
				}
				break;
			case 2:
				if(!maze->isWall(i, j+1)){
					j++;
					route +='u';
				}
				break;
			case 4:
				if(!maze->isWall(i, j-1)){
					j--;
					route +='d';
				}
				break;
		}

	}
}