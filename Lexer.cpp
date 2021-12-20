#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QMarkAutomoton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "EofAutomaton.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
//    for(size_t i= 0; i < tokens.size(); i++) {
//        delete tokens.at(i);
//    }
//    for(size_t i= 0; i < automata.size(); i++) {
//        delete automata.at(i);
//    }

}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IdAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new BlockCommentAutomaton());
    automata.push_back(new EofAutomaton());
}

void Lexer::Run(std::string& input) {


    //std::cout << input << std::endl;


    int lineNumber = 1;
    int maxRead = 0;

    Automaton* maxAutomaton;
    while (input.size()>0)
    {
        maxRead = 0;
        int inputRead = 0;

        //gets rid of whitespace
        if (isspace(input.at(0))) {
            //std::cout << "there is a space" << input.at(0) << std::endl;
            if(input.at(0)=='\n')
                lineNumber++;

            input.erase(input.begin());
            continue;
        }

        //Parallel
        for (int i=0; i < (int)automata.size(); i++) {
            inputRead = automata.at(i)->Start(input);
            if(maxRead < inputRead){
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        //make token
        if(maxRead>0) {
            if (maxAutomaton->type != TokenType::COMMENT) {
                tokens.push_back(maxAutomaton->CreateToken(input.substr(0,maxRead),lineNumber));
                lineNumber += maxAutomaton->NewLinesRead();
            }
        } else {
            maxRead =1;
            //std::cout << "undefined token: " << input.at(0) << std::endl;
            tokens.push_back(new Token(TokenType::UNDEFINED, input.substr(0,1), lineNumber));
        }

        //update input
        //std::cout << maxRead << std::endl;
        input.erase(input.begin(), input.begin() +maxRead);


    }
    if (input.size()==0) {
        tokens.push_back(new Token(TokenType::END_OF_FILE, input.substr(0,0), lineNumber));
    }


//    for(int i=0; i < (int)tokens.size();i++) {
//        PrintToken(tokens.at(i));
//    }
//    std::cout << "Total Tokens = " << tokens.size() << std::endl;
}

void Lexer::PrintToken(Token* token) {
    std::cout << token->toString() << std::endl;
}

std::vector<Token*> Lexer::GetTokens() {

    return tokens;
}
