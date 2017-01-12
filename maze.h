#ifndef MAZE_H
#define MAZE_H
//sources: https://en.wikipedia.org/wiki/Maze_generation_algorithm

class Maze 
//abstract maze generator base class
{
  private:
	char* squares; //a pointer to a length*width length array of characters
	int length;
	int width;
  public:
	virtual Maze(int length, int width, int seed);//default maze has no walls

	virtual ~Maze();

	void set(unsigned int i; unsigned int j, char value);
	//sets wall <i,j> to be value

	char val(unsigned int i, unsigned int j); 
	//returns the character value of that spot in the maze.

	void show(); //prints an image of the maze to std::cout

	char* get(); //returns a pointer to the start of the maze
}

class RPrims : Maze 
//generates a maze using randomized Prim's algorithm
{
  private:
  public:
  	RPrims(int length, int width, int seed);
  	~Rprims();
}

#endif