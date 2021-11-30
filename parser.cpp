#include <queue>
#include "token.h"

void parse(queue <Token> tokens) {
	Token token;

	while (!tokens.empty()) {
		token = tokens.pop();
		idToken(token, tokens);
	}
}

void idToken (Token token, queue <Token> tokens) {
	switch (token.type) {
		case 0:
			expr(token, tokens);
			break;
		case 1:
			keyword(token, tokens);
			break;
		case 2:
			expr(token, tokens);
			break;
		case 4:
		case 5:	
		case 6:
		case 7:
		case 13:
			RO(token, tokens);
			break;
		case 14:
		case 15:
			expr(token, tokens);
			break;
		case 21:
			RO(token, tokens);
			break;
		default:
			//error
	}
}

//change all to same as R and pass by reference

void expr (Token token, queue <Token> tokens) {
	if (token.instance == "+") {
		expr(tokens.pop(), tokens);
	} else {
		N(token,tokens);
	}
}

void N (Token token, queue <Token> tokens) {
	if (token.instance == "/" || token.instance == "*") {
		N(tokens.pop(), tokens);
	} else {
		A(token, tokens);
	}
}

void A {
	if (token.instance == "-") {
		A(tokens.pop(), tokens);
	} else {
		M(token, tokens);
	}
}

void M {
	if (token.instance == ".") {
		M(tokens.pop(), tokens);
	} else {
		R(token, tokens);
	}
}

void R {
	if (token.instance == "(") {
		token = tokens.pop();
		expr(token, tokens);
		if (token.instance == ")") {
			expr(tokens.pop(), tokens);
		}
	} else if (token.type == 0 || token.type == 2) {
		expr(tokens.pop(), tokens);		
	}
}
void keyword {
	if (token.instance == "declare") {
		program(token, tokens);
	} else {
		stats(token, tokens);
	}
}

void program {
	vars(token, tokens);
	if (token.instance == "program") {
		token = tokens.pop();
		block(token, tokens);
	}
}

void vars {
	if (token.instance == "declare") {
		token = tokens.pop();
		if (token.type == 0) {
			token = tokens.pop();
			if (token.instance == "=") {
				token = tokens.pop();
				if (token.type == 2) {
					token = tokens.pop();
					if (token.instance == ";") {
						token = tokens.pop();
						vars(token, tokens);
					} else {
						//error
					}
				} else {
					//error
				}
			} else {
				//error
			}
		} else {
			//error
		}
	}
}

void block {
	if (token.instance == "start") {
		token = tokens.pop();
		vars(token, tokens);
		stats(token, tokens);
		if (token.instance == "stop") {
			token = token.pop();
		}
	}
}

void stats {
	stat(token, tokens);
	mstat(token, tokens);
}

void stat {
	
}

void RO {

}
