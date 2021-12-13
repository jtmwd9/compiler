#ifndef CODEGEN_H
#define CODEGEN_H
#include <queue>
#include <iostream>
#include <string>
#include "token.h"

using namespace std;

class CodeGen {
	public:
		queue <Token> t;
		string code;
		bool w;
		int l, t;

		void init (queue <Token> temp) {
			while (!temp.empty) {
				this->t.push(temp.front());
				temp.pop();
			}
		}

		string tempVar (int o) {
			string temp;

			if (o == 0) {

				this->l++;
			} else {

				this->t++;
			}

			return temp;
		}

		void gen () {
			this->w = false;
			this->code = "";
			this->l = this->t = 0;

			while(!this->t.empty) {
				if (this->t.front().instance == "declare") {
					while (this->t.front().instance != ";") {
						this->t.pop();
					}
				} else if (this->t.front().instance == "start") {
					this->t.pop();
				} else if (this->t.front().instance == "listen") {
					code += "READ ";
					this->t.pop();
					code += this->t.front().instance + "\n";
				} else if (this->t.front().instance == "talk") {
					code += "WRITE ";
					this->t.pop();
					code += this->t.front().instance + "\n";
				} else if (this->t.front().instance == "assign") {
					this->t.pop();
					code += this->t.front().instance + " = ";
					this->t.pop();
					this->t.pop();
					this->expr();
				} else if (this->t.front().instance == "jump") {
					this->t.pop();
					code += "BR " + this->t.front().instance + "\n";
				} else if (this->t.front().instance == "label") {
					this->t.pop();
					c += this->t.front() + ":\n";
				} else if (this->t.front().instance == "if") {
					this->t.pop();
					this->if_();
				} else if (this->t.front().instance == "while") {
					this->t.pop();
					this->loop();
				} else if (this->t.front().instance == "stop") {	
					this->stop();
				} else {
					this->t.pop();
				}
			}
		}
};

#endif
