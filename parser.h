#ifndef PARSE_H
#define PARSER_H
#include<queue>
#include "token.h"
#include "tree.h"

Tree parse(std::queue <Token> tokens);
void idToken (Token &token, std::queue <Token> &tokens);
int expr (Token &token, std::queue <Token> &tokens);
int N (Token &token, std::queue <Token> &tokens);
int A (Token &token, std::queue <Token> &tokens);
int M (Token &token, std::queue <Token> &tokens);
int R (Token &token, std::queue <Token> &tokens);
void  keyword (Token &token, std::queue <Token> &tokens);
void program (Token &token, std::queue <Token> &tokens);
int vars (Token &token, std::queue <Token> &tokens);
int block (Token &token, std::queue <Token> &tokens);
int stats (Token &token, std::queue <Token> &tokens);
int mstat (Token &token, std::queue <Token> &tokens);
int stat (Token &token, std::queue <Token> &tokens);
int in (Token &token, std::queue <Token> &tokens);
int out (Token &token, std::queue <Token> &tokens);
int if_ (Token &token, std::queue <Token> &tokens);
int loop (Token &token, std::queue <Token> &tokens);
int assign (Token &token, std::queue <Token> &tokens);
int label (Token &token, std::queue <Token> &tokens);
int goto_ (Token &token, std::queue <Token> &tokens);
int RO (Token &token, std::queue <Token> &tokens);

#endif
