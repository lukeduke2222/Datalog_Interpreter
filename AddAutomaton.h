
#ifndef CS236_PROJECT_2_ADDAUTOMATON_H
#define CS236_PROJECT_2_ADDAUTOMATON_H

#include "Automaton.h"

class AddAutomaton : public Automaton
{
public:
    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //CS236_PROJECT_1_ADDAUTOMATON_H
