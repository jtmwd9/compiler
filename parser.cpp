#include <queue>
#include "token.h"

void parse(queue <Token> tokens) {
	Token token;

	while (!tokens.empty()) {
		token = Tokens.pop();
		idToken(token, Tokens);
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
		expr(tokens.pop(), tokens);
		if (token.instance == ")") {
			expr(tokens.pop(), tokens);
		}
	} else if (token.type == 0 || token.type == 2) {
		expr(tokens.pop(), tokens);		
	}
}
void keyword {
	if (token.instance == "declare") {
		vars(token,tokens);
	} else if (token.instance == "listen" || token.instance == "talk" || token.instance == "if" || token.instance == "while" || token.instance == "assign" || token.instance == "jump" || token.instance == "label" || token.instance == "start") {
		stats(token, tokens);
	}
}

void RO {

}
