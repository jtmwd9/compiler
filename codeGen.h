#ifndef CODEGEN_H
#define CODEGEN_H
#include <queue>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include "token.h"

using namespace std;

class CodeGen {
	public:
		queue <Token> t;
		stack <string> wbuffer;
		queue <string> tempys;
		string code, tmp;
		bool w;
		int lp, tm;

		void init (queue <Token> temp) {
			while (!temp.empty()) {
				this->t.push(temp.front());
				temp.pop();
			};
		}

		string tempVar (int o) {
			stringstream ss;
			ss << this->lp;
			string temp;

			if (o == 0) {
				temp = ("l" + ss.str());
				this->lp++;
			} else {
				temp = ("t" + ss.str());
				this->tm++;
			}
			this->tempys.push(temp);
			return temp;
		}

		void stop () {
			if (this->w == true) {
				this->code += this->wbuffer.top();
				this->wbuffer.pop();
			}
			if (this->wbuffer.empty()) {
				w = false;
			} 
			this->t.pop();
		}

		void expr (string tempo) {
			string load, op, type;
			string store = tempo;
			if (this->t.front().instance == "(") {
				this->t.pop();
				load = this->t.front().instance;
				this->t.pop();
				store = this->tmp;
			} else {
				load = this->t.front().instance;
				this->t.pop();
			}
			while (this->t.front().instance == "/" ||this->t.front().instance == "*" ||this->t.front().instance == "+" ||this->t.front().instance == "-") {
				if (this->t.front().instance == "/") {
					this->t.pop();
					type = "DIV ";
					if (this->t.front().instance == "(") {
						this->tmp = tempVar(1);
						op = this->tmp;
						this->expr("");
					} else {
						op = this->t.front().instance;
						this->t.pop();
					}
				} else if (this->t.front().instance == "*") {
					this->t.pop();
					type = "MULT ";
					if (this->t.front().instance == "(") {
						this->tmp = tempVar(1);
						op = this->tmp;
						this->expr("");
					} else {
						op = this->t.front().instance;
						this->t.pop();
					}
				} else if (this->t.front().instance == "+") {
					this->t.pop();
					type = "ADD ";
					if (this->t.front().instance == "(") {
						this->tmp = tempVar(1);
						op = this->tmp;
						this->expr("");
					} else {
						op = this->t.front().instance;
						this->t.pop();
					}
				} else if (this->t.front().instance == "-") {
					this->t.pop();
					type = "SUB ";
					if (this->t.front().instance == "(") {
						this->tmp = tempVar(1);
						op = this->tmp;
						this->expr("");
					} else {
						op = this->t.front().instance;
						this->t.pop();
					}
				} else if (this->t.front().instance == ")") {
					this->t.pop();
				} 
				this->code += "LOAD " + load + "\n" + type + " " + op + "\n" + "STORE " + store + "\n";
			};
		}

		void if_ () {
			string op;
			this->tmp = tempVar(0);
			this->code += "LOAD " + this->t.front().instance + "\n";
			this->t.pop();
			op = this->t.front().instance;
			this->t.pop();
			if (op == "{") {
				op = this->t.front().instance;
				this->t.pop();
				this->t.pop();
			}
			if (op == "==") {
				this->code += ("SUB " + this->t.front().instance + "\nBRNEG " + this->tmp + "\n");
				this->code += ("BRPOS " + this->tmp + "\n");
			} else if (op == ">") {
				this->code += ("SUB " + this->t.front().instance + "\nBRNEG " + this->tmp + "\n");	
			} else if (op == "<") {
				this->code += ("SUB " + this->t.front().instance + "\nBRPOS " + this->tmp + "\n");
			}
			this->w = true;
			this->wbuffer.push(this->tmp);
			this->wbuffer.top() += ": ";
		}

		void loop () {
			this->tmp = tempVar(0);
			this->w = true;
			this->code += this->tmp + ": ";
			this->wbuffer.push("LOAD " + this->t.front().instance + "\n");
			this->t.pop();
			string op = this->t.front().instance;
			this->t.pop();
			if (op == "{") {
				op = this->t.front().instance;
				this->t.pop();
			}
			if (op == "==") {
				this->wbuffer.top() += "SUB " + this->t.front().instance + "\nBRNEG " + this->tmp + "\n";
				this->code += ("BRPOS " + this->tmp + "\n");
			} else if (op == ">") {
				this->wbuffer.top() += "SUB " + this->t.front().instance + "\nBRNEG " + this->tmp + "\n";	
			} else if (op == "<") {
				this->wbuffer.top() += "SUB " + this->t.front().instance + "\nBRPOS " + this->tmp + "\n";
			}
		}

		void gen () {
			this->w = false;
			this->code = "";
			this->lp = this->tm = 0;
			string temp;

			while(!this->t.empty()) {
				if (this->t.front().instance == "declare") {
					while (this->t.front().instance != ";") {
						this->t.pop();
					}
				} else if (this->t.front().instance == "start") {
					this->t.pop();
				} else if (this->t.front().instance == "listen") {
					this->code += "READ ";
					this->t.pop();
					this->code += this->t.front().instance + "\n";
				} else if (this->t.front().instance == "talk") {
					this->code += "WRITE ";
					this->t.pop();
					this->code += this->t.front().instance + "\n";
				} else if (this->t.front().instance == "assign") {
					this->t.pop();
					temp = this->t.front().instance;
					this->t.pop();
					this->t.pop();
					this->expr(temp);
				} else if (this->t.front().instance == "jump") {
					this->t.pop();
					this->code += "BR " + this->t.front().instance + "\n";
				} else if (this->t.front().instance == "label") {
					this->t.pop();
					this->code += this->t.front().instance + ": ";
				} else if (this->t.front().instance == "if") {
					this->t.pop();
					this->t.pop();
					this->if_();
				} else if (this->t.front().instance == "while") {
					this->t.pop();
					this->t.pop();
					this->loop();
				} else if (this->t.front().instance == "stop") {	
					this->stop();
					this->t.pop();
				} else {
					this->t.pop();
				}
			};
			while (!this->wbuffer.empty()) {
				this->code += this->wbuffer.top() + ": ";
				this->wbuffer.pop();
			}
			this->code += "STOP\n";
			while (!tempys.empty()) {
				this->code += (tempys.front() + " 0\n");
				tempys.pop(); 
			};
		}
};

#endif
