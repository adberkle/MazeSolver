#ifndef MAZE_H
#define MAZE_H
//sources: https://en.wikipedia.org/wiki/Maze_generation_algorithm

class Maze 
//abstract maze generator base class
{
	char* squares; //a pointer to a height*width height array of characters
	/*see set::Maze(unsigned int i; unsigned int j, bool isWall) definition 
	for description on how maze is arranged*/
protected:
	unsigned int height;
	unsigned int width;
public:
  	/*Requires:nothing
 	 *Effects:constructs a default maze with all squares as isWalls
 	 *Modifies:allocates maze to heap*/
	Maze(unsigned int h, unsigned int w, bool isWalls);

	/*Requires:nothing
 	 *Effects:Deletes maze
 	 *Modifies:frees memory for maze from heap*/
	~Maze();

	/*Requires: 0 <= i <= width, 0 <= j <= height
 	 *Effects:sets wall <i,j> to be value
 	 *Modifies:changes bit value in &squares corresponding to location i,j*/
	void set(unsigned int i, unsigned int j, bool isWall);

	/*Requires: 0 <= i <= width, 0 <= j <= height
 	 *Effects:returns whether the specified coordinates are a wall
 	 *Modifies:Nothing*/
	bool isWall(unsigned int i, unsigned int j); 

	/*Requires:nothing
 	 *Effects: prints an image of the maze to std::cout
 	 *Modifies:Nothing*/
	void show();

	/*Requires:nothing
 	 *Effects:returns a pointer to the start of the maze
 	 *Modifies:nothing*/
	char* get();
};

class RPrims : public Maze 
//generates a maze using randomized Prim's algorithm
{
public:
  	RPrims(unsigned int h, unsigned int w, int seed);
};

#endif