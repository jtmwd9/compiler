#include "scanner.h"
#include "token.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Token Scanner::generateToken (string instance, int lineNumber, int classifier) {
	Token temp;
	switch (classifier) {
		case -1:
			//error
			break;
		case 1:
			//check for keywords
			temp.setType(Identifier);
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

void Scanner::scan (string inp) {
	int state = 0;
	string instance = "";
	int lineNumber = 1;
	Table table;

	for (int i = 0; i < inp.length(); i++) {
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
			case ':':
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
					//unknown character error
				}
		}
		if (state == -1) {
			//error
		} else if (state >= 100) {	
			state = state % 100;
			Token toke = generateToken(instance, lineNumber, state);
			tokens.push_back(toke);
			toke.printToken();
			instance = "";
			state = 0;
			i--;	
		} else {
			if (inp[i] != ' ' && inp[i] != '\n' && inp[i] != '\t') {
				instance += inp[i];
			}
		}		
	}
}
