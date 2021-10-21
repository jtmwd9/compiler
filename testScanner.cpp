#include <fstream>
#include <string>
#include <iostream>
#include "scanner.h"

using namespace std;

void testScanner (string fileName) {

	ifstream myFile;
	myFile.open(fileName.c_str());
	string inp = "", line;
	while (getline(myFile, line)) { //turns file into a string
		inp += line;
		inp += '\n';
	}

	Scanner tester;
	tester.scan(inp);

}
