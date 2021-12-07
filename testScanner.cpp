#include <fstream>
#include <string>
#include <iostream>
#include <queue>
#include "token.h"
#include "scanner.h"

using namespace std;

queue <Token*> testScanner (string fileName) {
	queue <Token*> tokens;
	ifstream myFile;
	myFile.open(fileName.c_str());
	string inp = "", line;
	while (getline(myFile, line)) { //turns file into a string
		inp += line;
		inp += '\n';
	}

	Scanner tester;

	tokens = tester.scan(inp);

	
	return tokens;
}
