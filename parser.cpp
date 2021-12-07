#include <queue>
#include <cstdlib>
#include "token.h"
#include "parser.h"
#include "tree.h"

using namespace std;

Tree tree;

void parse(queue <Token> tokens) {
	Token token;

	while (!tokens.empty()) {
		token = tokens.front();
		tokens.pop();
		idToken(token, tokens);
	}
}

void idToken (Token &token, queue <Token> &tokens) {
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
		case 22:
			//end of file
		default:
			cout<<"ERROR UNEXPECTED TOKEN: "<< token.instance << endl;
			exit(EXIT_FAILURE);
	}
}

//change all to same as R and pass by reference

void expr (Token &token, queue <Token> &tokens) {
	if (token.instance == "+") {
		cout << "<expr> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
	} else {
		N(token,tokens);
	}
}

void N (Token &token, queue <Token> &tokens) {
	if (token.instance == "/" || token.instance == "*") {
		cout << "<N> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		N(token, tokens);
	} else {
		A(token, tokens);
	}
}

void A (Token &token, queue <Token> &tokens) {
	if (token.instance == "-") {
		cout << "<A> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		A(token, tokens);
	} else {
		M(token, tokens);
	}
}

void M (Token &token, queue <Token> &tokens) {
	if (token.instance == ".") {
		cout << "<M> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		M(token, tokens);
	} else {
		R(token, tokens);
	}
}

void R (Token &token, queue <Token> &tokens) {
	if (token.instance == "(") {
		cout << "<R> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
		if (token.instance == ")") {
			cout << "<expr> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
			expr(token, tokens);
		}
	} else if (token.type == 0 || token.type == 2) {
		cout << "<R> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);		
	}
}
void keyword (Token &token, queue <Token> &tokens) {
	if (token.instance == "declare") {
		program(token, tokens);
	} else {
		stats(token, tokens);
	}
}

void program (Token &token, queue <Token> &tokens) {
	tree.head.nt = "<program>";
	tree.head.token = NULL;
	node* one, two, three;
	one.nt = "<vars>";
	one.token = NULL;
	tree.head.next.push(one);
	vars(token, tokens, head.next[0]);
	if (token.instance == "program") {
		cout << "<program> : " << token.instance << endl;
		two.nt = "";
		two.token = token;
		tree.head.next.push(two);
		token = tokens.front();
		tokens.pop();
		three.nt = "<block>";
		three.token = NULL;
		tree.head.next.push(three);
		block(token, tokens, head.next[2]);
	} else {
		cout<<"ERROR EXPECTING TYPE <PROGRAM>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void vars (Token &token, queue <Token> &tokens, node* n) {
	if (token.instance == "declare") {
		node *one;
		one.nt = "";
		one.token = token;
		n->next.push(one);
		cout << "<vars> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		if (token.type == 0) {
			node *two;
			two->nt = "";
			two->token = token;
			n->next.push(two);
			cout << "<vars> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
			if (token.instance == "=") {
				node *three;
				three->nt = "";
				three->token = token;
				n->next.push(three);
				cout << "<vars> : " << token.instance << endl;
				token = tokens.front();
				tokens.pop();
				if (token.type == 2) {
					node *four;
					four->nt = "";
					four->token = token;
					n->next.push(four);
					cout << "<vars> : " << token.instance << endl;
					token = tokens.front();
					tokens.pop();
					if (token.instance == ";") {
						node *five;
						five->nt = "";
						five->token = token;
						n->next.push(five);
						cout << "<vars> : " << token.instance << endl;
						token = tokens.front();
						tokens.pop();
						node *six;
						six->nt = "<vars>";
						six->token = NULL;
						n->next.push(six);
						vars(token, tokens, n->next[5]);
					} else {
						cout<<"ERROR EXPECTING ';' FOR TYPE <VARS>, RECIEVED " << token.instance << endl;;
						exit(EXIT_FAILURE);
					}
				} else {
					cout<<"ERROR EXPECTING INTEGER FOR TYPE <VARS>, RECIEVED " << token.instance << endl;;
					exit(EXIT_FAILURE);
				}
			} else {
				cout<<"ERROR EXPECTING '=' FOR TYPE <VARS>, RECIEVED " << token.instance << endl;;
				exit(EXIT_FAILURE);
			}
		} else {
			cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <VARS>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	}
}

void block (Token &token, queue <Token> &tokens, node * n) {
	if (token.instance == "start") {
		node *one;
		one.nt = "";
		one.token = NULL;
		n->next.push_back(one);
		cout << "<block> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		vars(token, tokens);
		stats(token, tokens);
		if (token.instance == "stop") {
			cout << "<block> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
		} else {
			cout<<"ERROR EXPECTING 'STOP' FOR TYPE <BLOCK>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING 'START' FOR TYPE <BLOCK>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void stats (Token &token, queue <Token> &tokens) {
	stat(token, tokens);
	mstat(token, tokens);
}

void mstat (Token &token, queue <Token> &tokens) {
	if (token.instance == "listen"||token.instance == "talk"||token.instance == "if"||token.instance == "while"|| token.instance == "assign"||token.instance == "jump"){
		stat(token, tokens);
		mstat(token,tokens);
	}
}

void stat (Token &token, queue <Token> &tokens) {
	if (token.instance == "listen") {
		cout << "<stat> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		in(token, tokens);
		if (token.instance == ";") {
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "talk") {
		cout << "<stat> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		out(token, tokens);
		if (token.instance == ";") {
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "if") {
		cout << "<stat> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		if_(token, tokens);
		if (token.instance == ";") {
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "while") {
		cout << "<stat> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		loop(token, tokens);
		if (token.instance == ";") {
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "assign") {
		cout << "<stat> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		assign(token, tokens);
		if (token.instance == ";") {
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "jump") {
		cout << "<stat> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		goto_(token, tokens);
		if (token.instance == ";") {
			token = tokens.front();
			tokens.pop();
		}
	} else {
		block(token, tokens);
	}	
}

void in (Token &token, queue <Token> &tokens) {
	if (token.type == 0) {
		cout << "<in> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <IN>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void out (Token &token, queue <Token> &tokens) {
	expr(token, tokens);
}

void if_ (Token &token, queue <Token> &tokens) {
	if (token.instance == "[") {
		cout << "<if> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
		RO(token, tokens);
		expr(token, tokens);
		if (token.instance == "]") {
			cout << "<if> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
			if (token.instance == "then") {
				cout << "<if> : " << token.instance << endl;
				token = tokens.front();
				tokens.pop();
				stat(token, tokens);
				if (token.instance == "else") {
					cout << "<if> : " << token.instance << endl;
					token=tokens.front();
					tokens.pop();
					stat(token, tokens);
				}
			} else {
				cout<<"ERROR EXPECTING 'THEN' FOR TYPE <IF>, RECIEVED " << token.instance << endl;;
				exit(EXIT_FAILURE);
			}
		} else {
			cout<<"ERROR EXPECTING ']' FOR TYPE <IF>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING '[' FOR TYPE <IF>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void loop (Token &token, queue <Token> &tokens) {
	if (token.instance == "[") {
		cout << "<loop> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		expr(token, tokens);
		RO(token, tokens);
		expr(token, tokens);
		if (token.instance == "]") {
		cout << "<loop> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
			stat(token, tokens);
		} else {
			cout<<"ERROR EXPECTING ']' FOR TYPE <LOOP>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING '[' FOR TYPE <LOOP>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void assign (Token &token, queue <Token> &tokens) {
	if (token.type == 0) {
		cout << "<assign> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		if (token.instance == "=") {
		cout << "<assign> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
			expr(token, tokens);
		} else {
			cout<<"ERROR EXPECTING '=' FOR TYPE <ASSIGN>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <ASSIGN>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void label (Token &token, queue <Token> &tokens) {
	if (token.type == 0) {
		cout << "<label> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFER FOR TYPE <LABEL>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void goto_ (Token &token, queue <Token> &tokens) {
	if (token.type == 0) {
		cout << "<goto> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <GOTO>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

void RO (Token &token, queue <Token> &tokens){
	if (token.instance == ">" || token.instance == "<" || token.instance == "==" || token.instance == "%") {
		cout << "<RO> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
	} else if (token.instance == "{") {
		cout << "<RO> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		if (token.instance == "==") {
			cout << "<RO> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
			if (token.instance == "}") {
				cout << "<RO> : " << token.instance << endl;
				token = tokens.front();
				tokens.pop();
			} else {
				cout<<"ERROR EXPECTING '}' FOR TYPE <RO>, RECIEVED " << token.instance << endl;;
				exit(EXIT_FAILURE);
			}
		} else {
			cout<<"ERROR EXPECTING '==' FOR TYPE <RO>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING RELATIONAL OPERATOR FOR TYPE <RO>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}
