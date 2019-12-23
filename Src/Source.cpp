#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include "MazeGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {

	istringstream iss(argv[1]);
	int size;

	if (iss >> size) {
		srand(time(0));
		MazeGenerator maze(size);
		maze.generate();
	}
	else {
		cout << "Error: coudn't read the size;" << endl;
	}
	return 0;
}
