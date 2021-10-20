#include <string>
#include <iostream>
#include <fstream>
#include "testScanner.h"

using namespace std;

int main (int argc, char* argv[]) {
	string fileName;
	if (argc == 1) {
		string in;
		ofstream myFile;
		myFile.open("inputtestfile");
		while (getline(cin, in)) {
			myFile << in;
		}
		myFile.close();
		fileName = "testfile";
	} else if (argc == 2) {
		fileName = argv[1];
	} else {
		cout << "Incorrect arguments given. Refer to readme";
		return -1;
	}
	testScanner(fileName);
	return 0;
}
