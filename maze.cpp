#include "maze.h"
#include "iostream"
#include <string.h> //memset()
#include <vector>
#include <random>
#include <utility>

/*Requires:nothing
 *Effects:constructs a default maze with no walls
 *Modifies:allocates maze to heap*/
Maze::Maze(unsigned int h, unsigned int w, bool isWalls){
	int bytes = h*w/8 + (h*w % 8 != 0);
	squares = new char[bytes];//aka new char[ciel(h*w/8)]
	memset(squares, (isWalls?-1:0), bytes);
	height = h;
	width = w;
}


/*Requires:nothing
 *Effects:Deletes maze
 *Modifies:frees memory for maze from heap*/
Maze::~Maze(){
	delete[] squares;
}


/*Requires: 0 <= i <= width, 0 <= j <= height
 *Effects:sets wall <i,j> to be value
 *Modifies:changes bit value in &squares corresponding to location i,j*/
void Maze::set(unsigned int i, unsigned int j, bool isWall){
/*how maze is arranged in memory:location (i,j)=(0,0) is the first bit of the
 *first char pointed to by squares. location (i, j) is the (i*j mod 8) bit of 
 *the floor(i*j/8) byte pointed to by squares. There are ciel(i*j/8) allocated,
 *so there can be up to 7 extra bits
 */
	if(isWall){
		*(squares + (j*width+i)/8) |= 1 << (j*width+i)%8;
	} else {
		*(squares + (j*width+i)/8) &= ~(1 << (j*width+i)%8);
	}
	
}

/*Requires: 0 <= i <= width, 0 <= j <= height
 *Effects:returns whether the specified coordinates are a wall
 *Modifies:Nothing*/
bool Maze::isWall(unsigned int i, unsigned int j){
	return ((static_cast<char>(*(squares+(j*width+i)/8)) >> (j*width+i)%8) & 1);
}

/*Requires:nothing
 *Effects: prints an image of the maze to std::cout
 *Modifies:Nothing*/
void Maze::show(){
/*it might be more efficient to display whole blocks of the maze at once, but 
I prefer to view the maze this way because I can change the orientation with
respects to (i,j) and only need to make changes in isWall and set*/
	for(unsigned int j = 0; j < height; j++){
		for(unsigned int i = 0; i < width; i++){
			if (isWall(i,j)){
				std::cout << "W ";
			} else {
				std::cout << "_ ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

/*Requires:nothing
 *Effects:returns a pointer to the start of the maze
 *Modifies:nothing*/
char* Maze::get() {
	return squares;
}


RPrims::RPrims(unsigned int h, unsigned int w, int seed)
:Maze(h,w, true)
{
	std::mt19937_64 ranNum(seed);
	set(0,0,false);
	std::vector<std::pair<unsigned int, unsigned int> > walls;
	walls.push_back(std::make_pair(0u,1u));
	walls.push_back(std::make_pair(1u,0u));
	unsigned long index = 0;
	char neighbors = 0;
	std::pair<unsigned int, unsigned int>* wall;
	while(!walls.empty()){
		index = ranNum() % walls.size();//pick random wall in list
		wall = &(walls[index]);
		neighbors = 0;
		//if it only has one adjacent path, make it a path and add all adjacent walls
		if(wall->first + 1 < width){
			if(!isWall(wall->first + 1, wall->second)){
				neighbors++;
			} 
		}
		if(wall->first != 0){
			if(!isWall(wall->first - 1, wall->second)){
				neighbors++;
			} 
		}
		if(wall->second + 1 < width){
			if(!isWall(wall->first, wall->second + 1)){
				neighbors++;
			} 
		}
		if(wall->second != 0){
			if(!isWall(wall->first, wall->second - 1)){
				neighbors++;
			} 
		}
		if(neighbors < 2){
			set(wall->first, wall->second, false);
			if(wall->first + 1 < width){
				if(isWall(wall->first + 1, wall->second)){
					walls.push_back(std::make_pair(wall->first + 1u, wall->second));
				} 
			}
			if(wall->first != 0){
				if(isWall(wall->first - 1, wall->second)){
					walls.push_back(std::make_pair(wall->first - 1u, wall->second));
				} 
			}
			if(wall->second + 1 < width){
				if(isWall(wall->first, wall->second + 1)){
					walls.push_back(std::make_pair(wall->first, wall->second + 1u));
				} 
			}
			if(wall->second != 0){
				if(isWall(wall->first, wall->second - 1)){
					walls.push_back(std::make_pair(wall->first, wall->second - 1u));
				} 
			}
		}
		swap(walls[index], walls[walls.size()-1]);
		walls.pop_back();//remove wall
	}
}
