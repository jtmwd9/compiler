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
cout<<"pre print"<<endl;
	tree.printTree(tree.nodes[0], 0);
cout<<"post print"<<endl;
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

int expr (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<vars>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "+") {
		cout << "<expr> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, expr(token, tokens));
	} else {
cout <<"expr"<<endl;
		tree.addNode(index, N(token,tokens));
	}
	return (index);
}

int N (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<vars>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "/" || token.instance == "*") {
		cout << "<N> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, N(token, tokens));
	} else {
		tree.addNode(index, A(token, tokens));
	}
	return (index);
}

int A (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<vars>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "-") {
		cout << "<A> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, A(token, tokens));
	} else {
		tree.addNode(index, M(token, tokens));
	}
	return (index);
}

int M (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<vars>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == ".") {
		cout << "<M> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, M(token, tokens));
	} else {
		tree.addNode(index, R(token, tokens));
	}
	return (index);
}

int R (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<vars>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "(") {
		cout << "<R> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, expr(token, tokens));
		if (token.instance == ")") {
			cout << "<expr> : " << token.instance << endl;
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
			tree.addNode(index, expr(token, tokens));
		}
	} else if (token.type == 0 || token.type == 2) {
		cout << "<R> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, expr(token, tokens));		
	}
	return (index);
}
int keyword (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<vars>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "declare" || token.instance == "program") {
		program(token, tokens);
	} else {
		tree.addNode(index, stats(token, tokens));
	}
	return (index);
}

void program (Token &token, queue <Token> &tokens) {
	node h;
	h.nt = "<program>";
	h.toke = token;
	tree.nodes.push_back(h);
	tree.addNode(0, vars(token, tokens));
	if (token.instance == "program") {
		cout << "<program> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(0, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(0, block(token, tokens));
	} else {
		cout<<"ERROR EXPECTING TYPE <PROGRAM>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
}

int vars (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<vars>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "declare") {
		cout << "<vars> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		if (token.type == 0) {
			cout << "<vars> : " << token.instance << endl;
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
			if (token.instance == "=") {
				cout << "<vars> : " << token.instance << endl;
				node n3;
				n3.toke = token;
				n3.nt = "";
				int index3 = tree.nodes.size();
				tree.nodes.push_back(n3);
				tree.addNode(index, index3);
				token = tokens.front();
				tokens.pop();
				if (token.type == 2) {
					cout << "<vars> : " << token.instance << endl;
					node n4;
					n4.toke = token;
					n4.nt = "";
					int index4 = tree.nodes.size();
					tree.nodes.push_back(n4);
					tree.addNode(index, index4);
					token = tokens.front();
					tokens.pop();
					if (token.instance == ";") {
						cout << "<vars> : " << token.instance << endl;
						node n5;
						n5.toke = token;
						n5.nt = "";
						int index5 = tree.nodes.size();
						tree.nodes.push_back(n5);
						tree.addNode(index, index5);
						token = tokens.front();
						tokens.pop();
						tree.addNode(index, vars(token, tokens));
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
	return (index);
}

int block (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "start") {
		cout << "<block> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, vars(token, tokens));
		tree.addNode(index, stats(token, tokens));
cout <<"back from stats"<<endl;
		if (token.instance == "stop") {
cout <<"stop"<<endl;
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
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
	return (index);
}

int stats (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	tree.addNode(index, stat(token, tokens));
	tree.addNode(index, mstat(token, tokens));

	return (index);
}

int mstat (Token &token, queue <Token> &tokens) {
cout <<"enter mstat"<<endl;
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "listen"||token.instance == "talk"||token.instance == "if"||token.instance == "while"|| token.instance == "assign"||token.instance == "jump") {
		tree.addNode(index, stat(token, tokens));
		tree.addNode(index, mstat(token, tokens));
	}
	return (index);
}

int stat (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "listen") {
		cout << "<stat> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, in(token, tokens));
cout <<"post in"<<endl;
		if (token.instance == ";") {
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
cout <<"post ;"<<endl;
		}
	} else if (token.instance == "talk") {
		cout << "<stat> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, out(token, tokens));
		if (token.instance == ";") {
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "if") {
		cout << "<stat> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, if_(token, tokens));
		if (token.instance == ";") {
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "while") {
		cout << "<stat> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, loop(token, tokens));
		if (token.instance == ";") {
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "assign") {
		cout << "<stat> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, assign(token, tokens));
		if (token.instance == ";") {
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
		}
	} else if (token.instance == "jump") {
		cout << "<stat> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, goto_(token, tokens));
		if (token.instance == ";") {
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
		}
	} else {
		tree.addNode(index, block(token, tokens));
	}	
	return (index);
}

int in (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.type == 0) {
		node n2;
		n2.toke = token;
		n2.nt = "";
		int index2 = tree.nodes.size();
		tree.nodes.push_back(n2);
		tree.addNode(index, index2);
		cout << "<in> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
cout <<"end of in"<<endl;
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <IN>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
	return (index);
}

int out (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	tree.addNode(index, expr(token, tokens));
	return (index);
}

int if_ (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "[") {	
		cout << "<if> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, expr(token, tokens));
cout <<"pre if RO"<<endl;
		tree.addNode(index, RO(token, tokens));
cout << "if to expr"<<endl;
		tree.addNode(index, expr(token, tokens));
		if (token.instance == "]") {
			cout << "<if> : " << token.instance << endl;
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
			if (token.instance == "then") {
				cout << "<if> : " << token.instance << endl;
				node n3;
				n3.toke = token;
				n3.nt = "";
				int index3 = tree.nodes.size();
				tree.nodes.push_back(n3);
				tree.addNode(index, index3);
				token = tokens.front();
				tokens.pop();
				tree.addNode(index, stat(token, tokens));
				if (token.instance == "else") {
					cout << "<if> : " << token.instance << endl;
					node n4;
					n4.toke = token;
					n4.nt = "";
					int index4 = tree.nodes.size();
					tree.nodes.push_back(n4);
					tree.addNode(index, index4);
					token=tokens.front();
					tokens.pop();
					tree.addNode(index, stat(token, tokens));
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
	return (index);
}

int loop (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == "[") {
		cout << "<loop> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		tree.addNode(index, expr(token, tokens));
		tree.addNode(index, RO(token, tokens));
		tree.addNode(index, expr(token, tokens));
		if (token.instance == "]") {
		cout << "<loop> : " << token.instance << endl;
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
			tree.addNode(index, stat(token, tokens));
		} else {
			cout<<"ERROR EXPECTING ']' FOR TYPE <LOOP>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING '[' FOR TYPE <LOOP>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
	return (index);
}

int assign (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.type == 0) {
		cout << "<assign> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
		if (token.instance == "=") {
		cout << "<assign> : " << token.instance << endl;
			node n2;
			n2.toke = token;
			n2.nt = "";
			int index2 = tree.nodes.size();
			tree.nodes.push_back(n2);
			tree.addNode(index, index2);
			token = tokens.front();
			tokens.pop();
			tree.addNode(index, expr(token, tokens));
		} else {
			cout<<"ERROR EXPECTING '=' FOR TYPE <ASSIGN>, RECIEVED " << token.instance << endl;;
			exit(EXIT_FAILURE);
		}
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <ASSIGN>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
	return (index);
}

int label (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.type == 0) {
		cout << "<label> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFER FOR TYPE <LABEL>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
	return (index);
}

int goto_ (Token &token, queue <Token> &tokens) {
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.type == 0) {
		cout << "<goto> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
	} else {
		cout<<"ERROR EXPECTING IDENTIFIER FOR TYPE <GOTO>, RECIEVED " << token.instance << endl;;
		exit(EXIT_FAILURE);
	}
	return (index);
}

int RO (Token &token, queue <Token> &tokens){
	node n;
	n.toke = token;
	n.nt = "<block>";
	int index = tree.nodes.size();
	tree.nodes.push_back(n);
	if (token.instance == ">" || token.instance == "<" || token.instance == "==" || token.instance == "%") {
		cout << "<RO> : " << token.instance << endl;
		node n1;
		n1.toke = token;
		n1.nt = "";
		int index1 = tree.nodes.size();
		tree.nodes.push_back(n1);
		tree.addNode(index, index1);
		token = tokens.front();
		tokens.pop();
	} else if (token.instance == "{") {
		node n2;
		n2.toke = token;
		n2.nt = "";
		int index2 = tree.nodes.size();
		tree.nodes.push_back(n2);
		tree.addNode(index, index2);
		cout << "<RO> : " << token.instance << endl;
		token = tokens.front();
		tokens.pop();
		if (token.instance == "==") {
			node n3;
			n3.toke = token;
			n3.nt = "";
			int index3 = tree.nodes.size();
			tree.nodes.push_back(n3);
			tree.addNode(index, index3);
			cout << "<RO> : " << token.instance << endl;
			token = tokens.front();
			tokens.pop();
			if (token.instance == "}") {
				cout << "<RO> : " << token.instance << endl;
				node n4;
				n4.toke = token;
				n4.nt = "";
				int index4 = tree.nodes.size();
				tree.nodes.push_back(n4);
				tree.addNode(index, index4);
cout <<"RO"<<endl;
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
	return (index);
}
