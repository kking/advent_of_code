// Advent of Code 2020, Day 2: Password Philosophy
// kking, 12/02/20

// Part 1:
// "...the North Pole Toboggan Rental Shop... password database seems to be a little corrupted...
// To try to debug the problem, they have created a list (your puzzle input) of passwords (according 
// to the corrupted database) and the corporate policy when that password was set.
// ... Each line gives the password policy and then the password. The password policy indicates the 
// lowest and highest number of times a given letter must appear for the password to be valid. For 
// example, 1-3 a means that the password must contain a at least 1 time and at most 3 times.
// ... How many passwords are valid according to their policies?"

// Part 2:
// "Each policy... describes two positions in the password, where 1 means the first character, 2 
// means the second character, and so on. (Be careful; Toboggan Corporate Policies have 
// no concept of "index zero"!) Exactly one of these positions must contain the given letter. Other 
// occurrences of the letter are irrelevant...
// ... How many passwords are valid according to the new interpretation of the policies?"

#include <fstream>  // std::ifstream
#include <iostream> // std::cout
#include <string>   // std::string, std::stoi

// If isPolicyOne is true, this method executes the solution for Part 1, where a valid password 
// must contain a specified character within the bounds of an inclusive minimum and maximum.
// Otherwise, the solution for Part 2 is executed, where a valid password contains the character
// at only one of the two positions indicated.
//
// @param fileName     The .txt file name received from command line input.
// @param isPolicyOne  true to determine validity under first policy logic, false for second policy
// @return             The number of valid passwords in the file.
int getNumValid(std::string fileName, bool isPolicyOne)
{
	std::string range, letter, password; // raw range, letter, password from file
	std::size_t charIndex; // index of '-' in range
	
	int min, max; // min and max count of a specified character in password
	int charCount; // count of the character
	int numValid = 0; // number of valid passwords
	
	// open an ifstream for the indicated file
	std::ifstream inFile; inFile.open(fileName.c_str());
	
	if (!inFile.is_open()) {
		return -1;
	}
	
	while (!inFile.eof()) {
		inFile >> range >> letter >> password; // read raw range, letter, and password
		
		// parse range into min and max
		charIndex = range.find("-");
		min = std::stoi(range.substr(0, charIndex));
		max = std::stoi(range.substr(charIndex+1));
		
		if (isPolicyOne) {
			// Policy One logic:
			// count frequency of specified character in password
			charCount = 0;
			for (int i = 0; i < password.length(); i++) {
				if (password[i] == letter[0]) {
					charCount++;
				}
			}
			// determine if password is valid
			if ((charCount >= min) && (charCount <= max)) {
				numValid++;
			}
		}
		else {
			// Policy Two logic:
			// use min and max as positions in password
			// note: offset from index 0, ^ = XOR
			if (((password[min-1] == letter[0]) ^ (password[max-1]) == letter[0])) {
				numValid++;
			}
		}
	}
	return numValid;
}

// for command-line argument execution
int main(int argc, char *argv[])
{
	if (argc == 2) {
		std::cout << "Number of valid passwords through Policy One: " << getNumValid(argv[1], true) << std::endl;
		std::cout << "Number of valid passwords through Policy Two: " << getNumValid(argv[1], false) << std::endl;
		return 0;
	}
	return -1;
}

