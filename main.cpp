#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include "token.h"
#include "testScanner.h"
#include "parser.h"
#include "tree.h"

using namespace std;

int main (int argc, char* argv[]) {
	string fileName, outfile;
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
		outfile = "kb.asm";
	} else if (argc == 2) {
		fileName = argv[1];
		outfile = fileName;
		outfile += ".asm";
	} else {
		cout << "Incorrect arguments given. Refer to readme";
		return -1;
	}

	tokens = testScanner(fileName);
	Token temp;
	CodeGen cg;
	temp.setType(EndOfFile);
	temp.setInstance("EndOfFile");
	tokens.push(temp);
	Tree tree;
	tree = parse(tokens);
	cg.init(tokens);
	cg.gen();
	for (int i = 0; i < tree.vals.size(); i++) {
		cg.code += (tree.vars[i] + " " + tree.vals[i] + "\n");
	}
	ofstream myfile;
	myfile.open(outfile.c_str());
	myfile << cg.code;
	myfile.close();
	cout << outfile << endl;
	return 0;
}
