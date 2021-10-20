#ifndef SCANNER_H
#define SCANNER_H
#include "tokenFSA.h"
#include "token.h"
#include <vector>
#include <string>

class Scanner {
	public:
		std::vector <Token> tokens;
		void scan(std::string);
		Token generateToken(std::string, int, int);
};

#endif
