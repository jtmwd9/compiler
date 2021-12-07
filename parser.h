#ifndef PARSE_H
#define PARSER_H
#include<queue>
#include"token.h"

void parse(std::queue <Token*> tokens);
void idToken (Token* &token, std::queue <Token*> &tokens);
void expr (Token* &token, std::queue <Token*> &tokens);
void N (Token* &token, std::queue <Token*> &tokens);
void A (Token* &token, std::queue <Token*> &tokens);
void M (Token* &token, std::queue <Token*> &tokens);
void R (Token* &token, std::queue <Token*> &tokens);
void keyword (Token* &token, std::queue <Token*> &tokens);
void program (Token* &token, std::queue <Token*> &tokens);
void vars (Token* &token, std::queue <Token*> &tokens);
void block (Token* &token, std::queue <Token*> &tokens);
void stats (Token* &token, std::queue <Token*> &tokens);
void mstat (Token* &token, std::queue <Token*> &tokens);
void stat (Token* &token, std::queue <Token*> &tokens);
void in (Token* &token, std::queue <Token*> &tokens);
void out (Token* &token, std::queue <Token*> &tokens);
void if_ (Token* &token, std::queue <Token*> &tokens);
void loop (Token* &token, std::queue <Token*> &tokens);
void assign (Token* &token, std::queue <Token*> &tokens);
void label (Token* &token, std::queue <Token*> &tokens);
void goto_ (Token* &token, std::queue <Token*> &tokens);
void RO (Token* &token, std::queue <Token*> &tokens);

#endif
