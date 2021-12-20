#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;

    void CreateAutomata();


public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);


    void PrintToken(Token* tokens);
    std::vector<Token*> GetTokens();
    

};
//make function that prints 1 token and run through for loop
#endif // LEXER_H

