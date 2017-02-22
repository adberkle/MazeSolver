#include "routeFinder.h"
#include "iostream"
#include <random>
#include <algorithm>
#include <stack>

RouteFinder::RouteFinder(Maze* mazeIn):maze(mazeIn),route(""){}
//RouteFinder::~RouteFinder(){}

/*Requires:N/A
 *Effects:visually displays route taken to get to goal
 *Modifies:N/A*/
void RouteFinder::display(){
	 std::cout << route << std::endl;
}

/*Requires:navigate() must have been run first
 *Effects:verifies the route used leads to the exit
 *Modifies:N/A*/
bool RouteFinder::verify(){
	unsigned int i = 0;
	unsigned int j = 0;
	for(unsigned int idx = 0; idx < route.length(); idx++){
	 	switch(route[idx]){
	 		case '<':
	 			i--;
	 			if(maze->isWall(i,j))
	 				return false;
	 			break;
	 		case '>':
	 			i++;
	 			if(maze->isWall(i,j))
	 				return false;
	 			break;
	 		case '^':
	 			j--;
	 			if(maze->isWall(i,j))
	 				return false;
	 			break;
	 		case 'v':
	 			j++;
	 			if(maze->isWall(i,j))
	 				return false;
	 			break;
	 	}
	}
	if(i+1 == maze->width && j+1 == maze->height)
	 	return true;
	return false;
}
RandomRoute::RandomRoute(Maze* mazeIn, int seedIn):RouteFinder(mazeIn),i(0u),
	j(0u),seed(seedIn){}

RandomRoute::~RandomRoute(){}

/*Requires:N/A
 *Effects:runs navigation on maze
 *Modifies:N/A*/
void RandomRoute::navigate(){
	int direction;
	std::mt19937_64 ranNum(seed);
	while(j + 1 != maze->height || i + 1 != maze->width){
		direction = ranNum() % 3;
		
		switch(direction) {
			case 0:
				if(i+1 !=  maze->width && !maze->isWall(i+1, j)){
					i++;
					route +='>';
				}
				break;
			case 1:
				if(i != 0 && !maze->isWall(i-1, j)){
					i--;
					route +='<';
				}
				break;
			case 2:
				if(j+1 != maze->height && !maze->isWall(i, j+1)){
					j++;
					route +='v';
				}
				break;
			case 4:
				if(j != 0 && !maze->isWall(i, j-1)){
					j--;
					route +='^';
				}
				break;
		}

	}
}



DepthFirst::DepthFirst(Maze* mazeIn):RouteFinder(mazeIn){}

DepthFirst ::~DepthFirst(){
}

DepthFirst::Node::Node(unsigned int x, unsigned int y, unsigned int parentIndex){
	i = x;
	j = y;
	parent = parentIndex;
};

void DepthFirst ::navigate(){
	Maze map(maze->height, maze->width, true);
	std::vector<Node> nodes;
	std::stack<unsigned int> lifoNodeIndexes;
	unsigned int index = 0;
	nodes.push_back(Node(0u,0u,-1));
	lifoNodeIndexes.push(0);
	map.set(0, 0, false);

	while((nodes[index].j + 1 != maze->height || nodes[index].i + 1 != maze->width)){
		index = lifoNodeIndexes.top();
		lifoNodeIndexes.pop();
		if(nodes[index].i + 1 < maze->width){
			if(!maze->isWall(nodes[index].i + 1, nodes[index].j) &&
				  map.isWall(nodes[index].i + 1, nodes[index].j)){
				map.set(nodes[index].i + 1, nodes[index].j, false);
				lifoNodeIndexes.push(nodes.size());
				nodes.push_back(Node(nodes[index].i + 1,nodes[index].j, index));
			} 
		}
		if(nodes[index].i != 0){
			if(!maze->isWall(nodes[index].i - 1, nodes[index].j) &&
				  map.isWall(nodes[index].i - 1, nodes[index].j)){
				map.set(nodes[index].i - 1, nodes[index].j, false);
				lifoNodeIndexes.push(nodes.size());
				nodes.push_back(Node(nodes[index].i - 1,nodes[index].j, index));	
			} 
		}
		if(nodes[index].j + 1 < maze->height){
			if(!maze->isWall(nodes[index].i, nodes[index].j + 1) &&
				  map.isWall(nodes[index].i, nodes[index].j + 1)){
				map.set(nodes[index].i, nodes[index].j + 1, false);
				lifoNodeIndexes.push(nodes.size());
				nodes.push_back(Node(nodes[index].i,nodes[index].j + 1, index));
			} 
		}
		if(nodes[index].j != 0){
			if(!maze->isWall(nodes[index].i, nodes[index].j - 1) &&
				  map.isWall(nodes[index].i, nodes[index].j - 1)){
				map.set(nodes[index].i, nodes[index].j - 1, false);
				lifoNodeIndexes.push(nodes.size());
				nodes.push_back(Node(nodes[index].i,nodes[index].j - 1, index));
				
			} 
		}
	}

	while(nodes[index].parent != -1){
		if(nodes[index].i == nodes[nodes[index].parent].i){
			if(nodes[index].j > nodes[nodes[index].parent].j){
				route += 'v';
			} else {
				route += '^';
			}
		} else {
			if(nodes[index].i > nodes[nodes[index].parent].i){
				route += '>';
			} else {
				route += '<';
			}
		}
		index = nodes[index].parent;
	}
	std::reverse(route.begin(),route.end());
}
