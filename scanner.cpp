#include "scanner.h"
#include <string>
#include <queue>
#include <iostream>

using namespace std;

Token Scanner::generateToken (string instance, int lineNumber, int classifier) {	//sets values for token and checks if identifiers are keywords
	Token temp;
	string keywords [15] = {"start", "stop", "while", "for", "label", "exit", "listen", "talk", "program"
				"if", "then", "assign", "declare", "jump", "else"};

	switch (classifier) {
		case -1:
			//error
			break;
		case 1:

			temp.setType(Identifier);

			for (int i = 0; i < 15; i++) {

				if (instance == keywords[i]){
					temp.setType(Keyword);
				}
			}
			break;
		case 2:
			temp.setType(Number);
			break;
		case 3:
			temp.setType(Equal);
			break;
		case 4: 
			temp.setType(EqualEqual);
			break;
		case 5:
			temp.setType(GreaterThan);
			break;
		case 6:
			temp.setType(LessThan);
			break;
		case 7:
			temp.setType(Colon);
			break;
		case 8:
			temp.setType(ColonEqual);
			break;
		case 9:
			temp.setType(Plus);
			break;
		case 10:
			temp.setType(Minus);
			break;
		case 11:
			temp.setType(Multiply);
			break;
		case 12:
			temp.setType(Divide);
			break;
		case 13:
			temp.setType(Modulo);
			break;
		case 14:
			temp.setType(Period);
			break;
		case 15:
			temp.setType(OpenParenthesis);
			break;
		case 16:
			temp.setType(ClosedParenthesis);
			break;
		case 17:
			temp.setType(Comma);
			break;
		case 18:
			temp.setType(OpenBracket);
			break;
		case 19:
			temp.setType(ClosedBracket);
			break;
		case 20:
			temp.setType(OpenBrace);
			break;
		case 21:
			temp.setType (ClosedBrace);;
			break;
	}

	temp.setLineNumber (lineNumber);
	temp.setInstance (instance);
	return temp;
}

queue <Token> Scanner::scan (string inp) {			//runs string through FSA
	int state = 0;
	string instance = "";
	int lineNumber = 1;
	Table table;

	for (int i = 0; i < inp.length(); i++) {
		if (inp[i] == '&'  && inp[i + 1] == '&') {	//ignores comnments
			i += 3;
			while (inp[i - 1] != '&'){
				i++;
			}
			i++;
		}
		switch (inp[i]) {
			case '$':
				state = table.tokenTable[state][1];
				break;
			case '=':
				state = table.tokenTable[state][5];
				break;
			case '>':
				state = table.tokenTable[state][6];
				break;
			case '<':
				state = table.tokenTable[state][7];
				break;
			case ';':
				state = table.tokenTable[state][8];
				break;
			case '+':
				state = table.tokenTable[state][9];
				break;
			case '-':
				state = table.tokenTable[state][10];
				break;
			case '*':
				state = table.tokenTable[state][11];
				break;
			case '/':
				state = table.tokenTable[state][12];
				break;
			case '%':
				state = table.tokenTable[state][13];
				break;
			case '.':
				state = table.tokenTable[state][14];
				break;
			case '(':
				state = table.tokenTable[state][15];
				break;
			case ')':
				state = table.tokenTable[state][16];
				break;
			case ',':
				state = table.tokenTable[state][17];
				break;
			case '{':
				state = table.tokenTable[state][18];
				break;
			case '}':
				state = table.tokenTable[state][19];
				break;
			case '[':
				state = table.tokenTable[state][20];
				break;
			case ']':
				state = table.tokenTable[state][21];
				break;
			case ' ':
				state = table.tokenTable[state][22];
				break;
			case '\t':
				state = table.tokenTable[state][22];
				break;
			case '\n':
				state = table.tokenTable[state][22];
				lineNumber++;
				break;
			default:
				if (islower(inp[i])){
					state = table.tokenTable[state][2];
				} else if (isupper(inp[i])){
					state = table.tokenTable[state][3];
				} else if (isdigit(inp[i])){
					state = table.tokenTable[state][4];
				} else {
					cout << "[UNKNOWN CHARACTER]";
				}
		}
		if (state == -1) {
			cout << "[ERROR]"; //will add better error functionality when I know more about language
		} else if (state >= 100) { //final state
			state = state % 100;

			Token toke;
			toke = generateToken(instance, lineNumber, state);

			tokens.push(toke);	//made a vector of tokens. don't really use it for this projects, but figured i might need it later

			//toke->printToken();
			instance = "";
			state = 0;
			i--;	
		} else {
			if (inp[i] != ' ' && inp[i] != '\n' && inp[i] != '\t') {
				instance += inp[i];
			}
		}		
	}
	return tokens;
}
