#ifndef TREE_H
#define TREE_H
#include <vector>
#include <string>
#include <iostream>
#include "token.h"
#include "codeGen.h"

struct node {
	Token toke;
	std::string nt;
	std::vector <node> next;
};

class Tree {
	public:
		node head;
		std::vector<node> nodes;
		std::vector <std::string> vars;
		std::vector <std::string> vals;
		CodeGen cg;
		void addNode (int i, int o) {
			node* nptr = &this->nodes[o];
			node* prevptr = &this->nodes[i];
			this->nodes[i].next.push_back(this->nodes[o]);
		}
		bool checkVar (std::string str) {
			bool c = false;
			for (int i = 0; i < this->vars.size(); i++) {
				if (this->vars[i] == str) {
					c = true;
				}
			}
			return c;
		}
		void startPrint () {
			std::cout << this->nodes[0].nt<<std::endl;
			printTree(this->nodes[0], 0);
		}
		void printTree (node n, int i) {
			int index;
	
			for (int o = 0; o < n.next.size(); o++) {
				std::cout << n.next[o].nt;
				if (n.next[o].nt == "") {
					std::cout << n.next[o].toke.instance << " ";
					i++;
				}
			}

			if (i == 0) {
				std::cout << std::endl;
			}

			for (int o = 0; o < n.next.size(); o++) {
				if (!n.next[o].next.empty()) {
					index = o;
				}
			}

			for (int o = 0; o < n.next.size(); o++) {
				if (!n.next[o].next.empty()) {
					if (index == o) {
						printTree (n.next[o], 0);
					} else {
						printTree (n.next[o], 1);
					}
				}
			}
		};
};


#endif
