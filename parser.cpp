#include <queue>
#include <cstdlib>
#include "token.h"
#include "parser.h"

using namespace std;

void parse(queue <Token*> tokens) {
	Token* token;

	while (!tokens.empty()) {
		token = tokens.front();
		tokens.pop();
		idToken(token, tokens);
	}
}

void idToken (Token* &token, queue <Token*> &tokens) {
	switch (token->type) {
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
			cout<<"ERROR UNEXPECTED TOKEN: "<< token->instance << endl;
			exit(EXIT_FAILURE);
	}
}

//change all to same as R and pass by reference

void expr (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "+") {
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
	} else {
		N(token,tokens);
	}
}

void N (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "/" || token->instance == "*") {
		token = tokens.front();
		tokens.pop();
		N(token, tokens);
	} else {
		A(token, tokens);
	}
}

void A (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "-") {
		token = tokens.front();
		tokens.pop();
		A(token, tokens);
	} else {
		M(token, tokens);
	}
}

void M (Token* &token, queue <Token*> &tokens) {
	if (token->instance == ".") {
		token = tokens.front();
		tokens.pop();
		M(token, tokens);
	} else {
		R(token, tokens);
	}
}

void R (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "(") {
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
		if (token->instance == ")") {
			token = tokens.front();
			tokens.pop();
			expr(token, tokens);
		}
	} else if (token->type == 0 || token->type == 2) {
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);		
	} else {
		cout<<"ERROR EXPECTING TYPE <R>"<<endl;
		exit(EXIT_FAILURE);
	}
}
void keyword (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "declare") {
		program(token, tokens);
	} else {
		stats(token, tokens);
	}
}

void program (Token* &token, queue <Token*> &tokens) {
	vars(token, tokens);
	if (token->instance == "program") {
		token = tokens.front();
		tokens.pop();
		block(token, tokens);
	} else {
		cout<<"ERROR EXPECTING TYPE <PROGRAM>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void vars (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "declare") {
		token = tokens.front();
		tokens.pop();
		if (token->type == 0) {
			token = tokens.front();
			tokens.pop();
			if (token->instance == "=") {
				token = tokens.front();
				tokens.pop();
				if (token->type == 2) {
					token = tokens.front();
					tokens.pop();
					if (token->instance == ";") {
						token = tokens.front();
						tokens.pop();
						vars(token, tokens);
					} else {
						cout<<"ERROR EXPECTING ';' FOR TYPE <VARS>"<<endl;
						exit(EXIT_FAILURE);
					}
				} else {
					cout<<"ERROR EXPECTING INTEGER FOR TYPE <VARS>"<<endl;
					exit(EXIT_FAILURE);
				}
			} else {
				cout<<"ERROR EXPECTING '=' FOR TYPE <VARS>"<<endl;
				exit(EXIT_FAILURE);
			}
		} else {
			cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <VARS>"<<endl;
			exit(EXIT_FAILURE);
		}
	}
}

void block (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "start") {
		token = tokens.front();
		tokens.pop();
		vars(token, tokens);
		stats(token, tokens);
		if (token->instance == "stop") {
			token = tokens.front();
			tokens.pop();
		} else {
			cout<<"ERROR EXPECTING 'STOP' FOR TYPE <BLOCK>"<<endl;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING 'START' FOR TYPE <BLOCK>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void stats (Token* &token, queue <Token*> &tokens) {
	stat(token, tokens);
	mstat(token, tokens);
}

void mstat (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "listen"||token->instance == "talk"||token->instance == "if"||token->instance == "while"|| token->instance == "assign"||token->instance == "jump"){
		stat(token, tokens);
		mstat(token,tokens);
	}
}

void stat (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "listen") {
		token = tokens.front();
		tokens.pop();
		in(token, tokens);
	} else if (token->instance == "talk") {
		token = tokens.front();
		tokens.pop();
		out(token, tokens);
	} else if (token->instance == "if") {
		token = tokens.front();
		tokens.pop();
		if_(token, tokens);
	} else if (token->instance == "while") {
		token = tokens.front();
		tokens.pop();
		loop(token, tokens);
	} else if (token->instance == "assign") {
		token = tokens.front();
		tokens.pop();
		assign(token, tokens);
	} else if (token->instance == "jump") {
		token = tokens.front();
		tokens.pop();
		goto_(token, tokens);
	} else {
		block(token, tokens);
	}	
}

void in (Token* &token, queue <Token*> &tokens) {
	if (token->type == 0) {
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <IN>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void out (Token* &token, queue <Token*> &tokens) {
	expr(token, tokens);
}

void if_ (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "[") {
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
		RO(token, tokens);
		expr(token, tokens);
		if (token->instance == "]") {
			token = tokens.front();
			tokens.pop();
			if (token->instance == "then") {
				token = tokens.front();
				tokens.pop();
				stat(token, tokens);
				if (token->instance == "else") {
					token=tokens.front();
					tokens.pop();
					stat(token, tokens);
				}
			} else {
				cout<<"ERROR EXPECTING 'THEN' FOR TYPE <IF>"<<endl;
				exit(EXIT_FAILURE);
			}
		} else {
			cout<<"ERROR EXPECTING ']' FOR TYPE <IF>"<<endl;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING '[' FOR TYPE <IF>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void loop (Token* &token, queue <Token*> &tokens) {
	if (token->instance == "[") {
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
		RO(token, tokens);
		expr(token, tokens);
		if (token->instance == "]") {
			token = tokens.front();
			tokens.pop();
			stat(token, tokens);
		} else {
			cout<<"ERROR EXPECTING ']' FOR TYPE <LOOP>"<<endl;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING '[' FOR TYPE <LOOP>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void assign (Token* &token, queue <Token*> &tokens) {
	if (token->type == 0) {
		token = tokens.front();
		tokens.pop();
		if (token->instance == "=") {
			token = tokens.front();
			tokens.pop();
			expr(token, tokens);
		} else {
			cout<<"ERROR EXPECTING '=' FOR TYPE <ASSIGN>"<<endl;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <ASSIGN>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void label (Token* &token, queue <Token*> &tokens) {
	if (token->type == 0) {
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFER FOR TYPE <LABEL>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void goto_ (Token* &token, queue <Token*> &tokens) {
	if (token->type == 0) {
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <GOTO>"<<endl;
		exit(EXIT_FAILURE);
	}
}

void RO (Token* &token, queue <Token*> &tokens){
	if (token->instance == ">" || token->instance == "<" || token->instance == "==" || token->instance == "%") {
		token = tokens.front();
		tokens.pop();
	} else if (token->instance == "{") {
		token = tokens.front();
		tokens.pop();
		if (token->instance == "==") {
			token = tokens.front();
			tokens.pop();
			if (token->instance == "}") {
				token = tokens.front();
				tokens.pop();
			} else {
				cout<<"ERROR EXPECTING '}' FOR TYPE <RO>"<<endl;
				exit(EXIT_FAILURE);
			}
		} else {
			cout<<"ERROR EXPECTING '==' FOR TYPE <RO>"<<endl;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING RELATIONAL OPERATOR FOR TYPE <RO>"<<endl;
		exit(EXIT_FAILURE);
	}
}
