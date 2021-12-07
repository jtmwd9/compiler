#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include "token.h"
#include "testScanner.h"
#include "parser.h"

using namespace std;

int main (int argc, char* argv[]) {
	string fileName;
	queue <Token> tokens;
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

	tokens = testScanner(fileName);
	Token temp;
	temp.setType(EndOfFile);
	temp.setInstance("EndOfFile");
	tokens.push(temp);
	parse(tokens);
	return 0;
}
