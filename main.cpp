#include <string>
#include <iostream>
#include <fstream>
#include "testScanner.h"

using namespace std;

int main (int argc, char* argv[]) {
	string fileName;
	if (argc == 1) {	//no command line args
		string in;
		ofstream myFile;	//puts keyboard input in a file to read later in testScanner.cpp
		myFile.open("inputtestfile");
		while (getline(cin, in)) {
			myFile << in;
			myFile << '\n';
		}
		myFile.close();
		fileName = "inputtestfile";
	} else if (argc == 2) {
		fileName = argv[1];
	} else {
		cout << "Incorrect arguments given. Refer to readme";
		return -1;
	}
	testScanner(fileName);
	return 0;
}
