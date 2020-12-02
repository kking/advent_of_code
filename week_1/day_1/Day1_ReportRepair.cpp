// Advent of Code 2020, Day 1: Report Repair
// kking, 12/01/20

// Part 1:
// "... the Elves in accounting just need you to fix your expense report (your puzzle input); 
// apparently, something isn't quite adding up.
// Specifically, they need you to find the two entries that sum to 2020 and then multiply those two 
// numbers together. 
// ...Find the two entries that sum to 2020; what do you get if you multiply them together?"

// Part 2:
// "In your expense report, what is the product of the three entries that sum to 2020?"

#include <fstream>  // for std::ifstream
#include <iostream> // for std::cout

// getTwoEntryProduct : Implementation of the Part 1 objective. 
// @param fileName  The .txt file name received from command line input.
// @param target    The current year and target sum.
// @return          The product of two entries whose sum is equal to target, or -1.
int getTwoEntryProduct(std::string fileName, int target) 
{
	int entry1, entry2;
	int inFile2pos = 0;
	
	// open two ifstreams for the indicated file
	std::ifstream inFile1; inFile1.open(fileName.c_str());
	std::ifstream inFile2; inFile2.open(fileName.c_str());
	
	if (!inFile1.is_open() || !inFile2.is_open()) {
		return -1;
	}
	
	// outer loop iterates through each entry once (worst case: O(n^2))
	while (inFile1 >> entry1) {
		inFile2pos = inFile1.tellg(); // record current position of stream 1
		
		// inner loop iterates through each entry starting from position of stream 1
		while (inFile2 >> entry2) {
			if ((entry1 + entry2) == target) {
				return (entry1 * entry2); // return product of the two entries
			}
		}
		inFile2.clear(); // reset position of stream 2 to start from
		inFile2.seekg(inFile2pos); // current position of stream 1
	}
	return -1;
	
} // end of getTwoEntryProduct

// getThreeEntryProduct : Implementation of the Part 2 objective. 
// @param fileName  The .txt file name received from command line input.
// @param target    The current year and target sum.
// @return          The product of two entries whose sum is equal to target, or -1.
int getThreeEntryProduct(std::string fileName, int target)
{
	int entry;
	int twoEntryProduct;
	
	// open an ifstream for the indicated file
	std::ifstream inFile; 
	inFile.open(fileName.c_str());
	
	if (!inFile.is_open()) {
		return -1;
	}
	
	// outermost loop iterates through each entry once (worst case: O(n^3))
	while (inFile >> entry) 
	{
		// obtain product of two entries whose sum is equal to target - the current entry
		twoEntryProduct = getTwoEntryProduct(fileName, (target - entry));
		if (twoEntryProduct > 0) {
			return (entry * twoEntryProduct); // return product of the three entries
		}
	}
	return -1;
	
} // end of getThreeEntryProduct

int main(int argc, char *argv[]) 
{
	if (argc == 2) {
		int year = 2020;
		std::cout << "Two-entry product = " << getTwoEntryProduct(argv[1], year) << std::endl;
		std::cout << "Three-entry product = " << getThreeEntryProduct(argv[1], year) << std::endl;
		return 0;
	}
	return -1;
}

