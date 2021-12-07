#ifndef SCANNER_H
#define SCANNER_H
#include "tokenFSA.h"
#include "token.h"
#include <queue>
#include <string>

class Scanner {
	public:
		std::queue <Token*> tokens;
		std::queue <Token*> scan(std::string);
		Token* generateToken(std::string, int, int);
};

#endif
