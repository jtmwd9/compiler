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
		queue <string> wbuffer;
		string code;
		bool w;
		int lp, tmp;

		void init (queue <Token> temp) {
			while (!temp.empty()) {
				this->t.push(temp.front());
				temp.pop();
			};
cout << "we got to init" << endl;
		}

		string tempVar (int o) {
			string temp;

			if (o == 0) {

				this->lp++;
			} else {

				this->tmp++;
			}

			return temp;
		}

		void stop () {
			if (this->w == true) {
				this->code += this->wbuffer.front();
				this->w = false;
				this->wbuffer.pop();
			}
			this->t.pop();
		}

		void expr () {
			this->code += "LOAD " + this->t.front().instance + "\n";
			this->t.pop();
			if (this->t.front().instance == "/") {

			} else if (this->t.front().instance == "*") {

			} else if (this->t.front().instance == "+") {

			} else if (this->t.front().instance == "-") {

			} 
		}

		void if_ () {

		}

		void loop () {

		}

		void gen () {
			this->w = false;
			this->code = "";
			this->wbuffer = "";
			this->lp = this->tmp = 0;
cout << this->t.front().instance << endl;
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
					this->expr();
					this->code += "STORE " + temp + "\n";
				} else if (this->t.front().instance == "jump") {
					this->t.pop();
					this->code += "BR " + this->t.front().instance + "\n";
				} else if (this->t.front().instance == "label") {
					this->t.pop();
					this->code += this->t.front().instance + ":\n";
				} else if (this->t.front().instance == "if") {
					this->t.pop();
					this->if_();
				} else if (this->t.front().instance == "while") {
					this->t.pop();
					this->loop();
				} else if (this->t.front().instance == "stop") {	
					this->stop();
					this->t.pop();
				} else {
					this->t.pop();
				}
			};
		}
};

#endif
