// Advent of Code 2020, Day 3: Toboggan Trajectory
// kking, 12/04/20

// Part 1:
// "... you set off toward the airport. While travel by toboggan might be easy, it's certainly not 
// safe: there's very minimal steering and the area is covered in trees. You'll need to see which 
// angles will take you near the fewest trees.
// Due to the local geology, trees in this area only grow on exact integer coordinates in a grid. 
// You make a map (your puzzle input) of the open squares (.) and trees (#) you can see.
// ... the same pattern repeats to the right many times...
// You start on the open square (.) in the top-left corner and need to reach the bottom (below 
// the bottom-most row on your map)...
// ... The toboggan can only follow a few specific slopes... start by counting all the trees you 
// would encounter for the slope... until you go past the bottom of the map.
// ... Starting at the top-left corner of your map and following a slope of right 3 and down 1, how 
// many trees would you encounter?"

// Part 2:
// "... Determine the number of trees you would encounter if, for each of the following slopes, you start 
// at the top-left corner and traverse the map all the way to the bottom:
// 		Right 1, down 1; 
// 		Right 3, down 1. (This is the slope you already checked.)
// 		Right 5, down 1.
// 		Right 7, down 1.
// 		Right 1, down 2.
// ... What do you get if you multiply together the number of trees encountered on each of the 
// listed slopes?"

#include <fstream>  // std::ifstream
#include <iostream> // std::cout

// Reads a text file presenting a map of open squares (.) and trees (#), recording the number of
// times a tree is hit from traversing a path of the indicated slope. 
//
// @param fileName  The .txt file name received from command line input.
// @param x         The horizontal difference in the slope.
// @param y         The vertical difference in the slope.
// @return          The number of trees encountered in the path.
int traverseMap(std::string fileName, int x, int y)
{
	int currentX = 0, currentY = y+1; // +1 to skip first line in map
	int numTrees = 0;
	std::string line;
	
	// open an ifstream
	std::ifstream inFile; 
	inFile.open(fileName.c_str());
	
	if (!inFile.is_open()) {
		return -1;
	}

	while (inFile >> line) {
		if (currentY == 1) {
			// reset y-step and update x-step (may wrap)
			currentX += x;
			if (currentX >= line.length()) currentX -= line.length();
			currentY = y;
			
			numTrees += (line[currentX] == '#'); // determine if a hit occurred
		}
		else {
			currentY--; // skip line
		}
	}

	return numTrees;
	
} // end of traverseMap

// for command-line argument execution
int main(int argc, char *argv[]) 
{
	if (argc == 2) {
		int numTrees[] = { 
				traverseMap(argv[1], 1, 1), 
				traverseMap(argv[1], 3, 1),
				traverseMap(argv[1], 5, 1), 
				traverseMap(argv[1], 7, 1),
				traverseMap(argv[1], 1, 2) };
		
		unsigned long int product = 1; // unsigned long int: 0 to 4,294,967,295
		for (int t : numTrees) {
			product *= t;
		}
		
		std::cout << "Trees encountered (m=1/1): " << numTrees[0] << std::endl;
		std::cout << "Trees encountered (m=3/1): " << numTrees[1] << std::endl;
		std::cout << "Trees encountered (m=5/1): " << numTrees[2] << std::endl;
		std::cout << "Trees encountered (m=7/1): " << numTrees[3] << std::endl;
		std::cout << "Trees encountered (m=1/2): " << numTrees[4] << std::endl;
		std::cout << "Product of all trees = " << product << std::endl;
		
		return 0;
	}
	return -1;
}

// error 1: wrap-around calculation condition resulted in currentX exceeding line.length()
// error 2: off-by-one error where the first row was read in path first (should start from top left)
// resolved by initializing currentY to y+1

