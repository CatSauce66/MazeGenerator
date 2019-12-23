#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(int width) {
	this->width = width;
	this->height = width;
}

void MazeGenerator::info() {
	cout << "Width of maze: " << width << endl;
	cout << "Height of maze: " << height << endl;
}

void MazeGenerator::generate() {
	//setup
	makeGrid();
	setWalkable();

	//begin
	startGeneration();

	//put print maze as last
	printMaze();
}

//PRIVATE METHODES------------------------

void MazeGenerator::startGeneration() {
	int posX = 1;
	int posY = 1;
	walkBack = false;

	while (true) {

		if (walkBack == false) {
			savePosition(posX, posY);
		}
		walkBack = false;


		checkDirections(posY, posX);
		randomIndex();

		walkable[posY][posX] = false; // can cause error while backtracking

		if (walkDir == 1) {
			grid[posY - 1][posX] = " ";
			posY = posY - 2;
		}
		if (walkDir == 2) {
			grid[posY][posX + 1] = " ";
			posX = posX + 2;
		}
		if (walkDir == 3) {
			grid[posY + 1][posX] = " ";
			posY = posY + 2;
		}
		if (walkDir == 4) {
			grid[posY][posX - 1] = " ";
			posX = posX - 2;
		}
		if (walkDir == 0) {
			backTrack(posX, posY);
		}

		//check if completed
		if (checkCompleted() == true) {
			return;
		}
	}
}

void MazeGenerator::makeGrid() {
	for (int i = 0; i < height * 2 + 1; i++) {
		vector <string> temp;
		for (int j = 0; j < width * 2 + 1; j++) {
			temp.push_back("X");
		}
		grid.push_back(temp);
	}

	//create the holes
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (j % 2 == 0 || i % 2 == 0) {
				grid[i][j] = "#";
			}
			else {
				grid[i][j] = " ";
			}

			if (j == 0 || j == grid[i].size() - 1) {
				grid[i][j] = "#";
			}
			if (i == 0 || i == grid.size() - 1) {
				grid[i][j] = "#";
			}

			//created entrace and exit
			if (j == 0 && i == 1) {
				grid[i][j] = " ";
			}
			if (j == grid[i].size() - 1 && i == grid.size() - 2) {
				grid[i][j] = " ";
			}
		}
	}

}

void MazeGenerator::printMaze() {
	for (int i = grid.size() - 1; i >= 0; i--) {
		for (int j = grid[i].size() - 1; j >= 0; j--) {
			cout << grid[i][j] << "";
			//cout << walkable[i][j] << " ";
		}
		cout << endl;
	}
}

void MazeGenerator::setWalkable() {
	for (int i = 0; i < grid.size(); i++) {
		vector <bool> temp;
		for (int j = 0; j < grid[i].size(); j++) {
			temp.push_back(true);
		}
		walkable.push_back(temp);
	}

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (j % 2 == 0 || i % 2 == 0) {
				walkable[i][j] = false;
			}
			else {
				walkable[i][j] = true;
			}

			if (j == 0 || j == grid[i].size() - 1) {
				walkable[i][j] = false;
			}
			if (i == 0 || i == grid.size() - 1) {
				walkable[i][j] = false;
			}
		}
	}
}

void MazeGenerator::randomIndex() {
	//before this methode run "checkDirections" to make a array of directions
	int i = rand() % direction.size();
	walkDir = direction[i];
}

void MazeGenerator::checkDirections(int h, int w) {
	if (direction.size() > 0) {
		direction.erase(direction.begin(), direction.end());
	}


	//checks the corners
	if (h == 1 && w == 1) {
		if (walkable[h][w + 2] == 1) {
			direction.push_back(2); //east
		}
		if (walkable[h + 2][w] == 1) {
			direction.push_back(3); //south
		}
	}
	else if (h == 1 && w == walkable[h].size() - 2) {
		if (walkable[h + 2][w] == 1) {
			direction.push_back(3); //south
		}
		if (walkable[h][w - 2] == 1) {
			direction.push_back(4); //west
		}
	}
	else if (h == walkable.size() - 2 && w == 1) {
		if (walkable[h - 2][w] == 1) {
			direction.push_back(1); //north
		}
		if (walkable[h][w + 2] == 1) {
			direction.push_back(2); //east
		}
	}
	else if (h == walkable.size() - 2 && w == walkable[h].size() - 2) {
		if (walkable[h - 2][w] == 1) {
			direction.push_back(1); //north
		}
		if (walkable[h][w - 2] == 1) {
			direction.push_back(4); //west
		}
	}

	//checks the sides
	else if (h == 1 && (w > 2 && w < walkable[h].size() - 3)) {
		if (walkable[h][w + 2] == 1) {
			direction.push_back(2); //east
		}
		if (walkable[h + 2][w] == 1) {
			direction.push_back(3); //south
		}
		if (walkable[h][w - 2] == 1) {
			direction.push_back(4); //west
		}
	}
	else if (h == walkable.size() - 2 && (w > 2 && w < walkable[h].size() - 3)) {
		if (walkable[h - 2][w] == 1) {
			direction.push_back(1); //north
		}
		if (walkable[h][w + 2] == 1) {
			direction.push_back(2); //east
		}
		if (walkable[h][w - 2] == 1) {
			direction.push_back(4); //west
		}
	}
	else if ((h > 2 && h < walkable.size() - 3) && w == 1) {
		if (walkable[h - 2][w] == 1) {
			direction.push_back(1); //north
		}
		if (walkable[h][w + 2] == 1) {
			direction.push_back(2); //east
		}
		if (walkable[h + 2][w] == 1) {
			direction.push_back(3); //south
		}
	}
	else if ((h > 2 && h < walkable.size() - 3) && w == walkable.size() - 2) {
		if (walkable[h - 2][w] == 1) {
			direction.push_back(1); //north
		}
		if (walkable[h + 2][w] == 1) {
			direction.push_back(3); //south
		}
		if (walkable[h][w - 2] == 1) {
			direction.push_back(4); //west
		}
	}
	else {
		if (walkable[h - 2][w] == 1) {
			direction.push_back(1); //north
		}
		if (walkable[h][w + 2] == 1) {
			direction.push_back(2); //east
		}
		if (walkable[h + 2][w] == 1) {
			direction.push_back(3); //south
		}
		if (walkable[h][w - 2] == 1) {
			direction.push_back(4); //west
		}
	}

	if (direction.size() == 0) {
		direction.push_back(0); //nothing
	}

	//cout << direction.size() << endl;
}

void MazeGenerator::savePosition(int x, int y) {
	oldPositions.push_back(x);
	oldPositions.push_back(y);
}

void MazeGenerator::backTrack(int& x, int& y) {
	oldPositions.pop_back();
	oldPositions.pop_back();

	x = oldPositions[oldPositions.size() - 2];
	y = oldPositions[oldPositions.size() - 1];
	walkBack = true;
}

bool MazeGenerator::checkCompleted() {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			if (walkable[i][j] == 1) {
				return false;
			}
		}
	}
	return true;
}
