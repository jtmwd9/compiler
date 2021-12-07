#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <string>

enum TokenType {Identifier, Keyword, Number, Equal, EqualEqual, GreaterThan, LessThan, Colon, ColonEqual, 
	        Plus, Minus, Multiply, Divide, Modulo, Period, OpenParenthesis, ClosedParenthesis, Comma,
	        OpenBracket, ClosedBracket, OpenBrace, ClosedBrace};

class Token {
	public:
		std::string tokenEnumNames [22] = {"Identifier", "Keyword", "Number", "Equal", "EqualEqual", "GreaterThan", 
					           "LessThan", "Colon", "ColonEqual", "Plus", "Minus", "Multiply", "Divide", 
			      			   "Modulo", "Period", "OpenParenthesis", "ClosedParenthesis", "Comma", 
			     			   "OpenBracket", "ClosedBracket", "OpenBrace", "ClosedBrace"};

		TokenType type;
		std::string instance;
		int lineNumber;
	//just defined functions here because they're so short
		void printToken() {
			std::cout << tokenEnumNames[this->type] << " " << this->instance << " " << this-> lineNumber << std::endl;
		}
		void setType(TokenType type) {

			this->type = type;

		}
		void setInstance(std::string instance) {
			this->instance = instance;
		}
		void setLineNumber(int lineNum) {
			this->lineNumber = lineNum;
		}
};

#endif
