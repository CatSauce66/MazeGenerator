#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class MazeGenerator
{
public:
	MazeGenerator(int width);
	void info();
	void generate();


private:
	void startGeneration(); //starts the maze generation
	void makeGrid(); //sets the grid
	void printMaze(); //prints the maze
	void setWalkable(); //sets at begining of program, the walls to not walkable
	void randomIndex(); //picks a random direction
	void checkDirections(int h, int w); //checks possible walk directions
	void savePosition(int x, int y); //saves position in a vector to later backtrack (move back)
	void backTrack(int& x, int& y); //moves back a spot and removes the position to complete the maze
	bool checkCompleted(); //check if the maze is completed


	int width;
	int height;
	int walkDir;
	bool walkBack;
	vector <vector<string>> grid;
	vector <vector<bool>> walkable;
	vector <int> direction;
	vector <int> oldPositions;
};

