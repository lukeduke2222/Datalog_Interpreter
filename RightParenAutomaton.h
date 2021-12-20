

#ifndef CS236_PROJECT_2_RIGHTPARENAUTOMATON_H
#define CS236_PROJECT_2_RIGHTPARENAUTOMATON_H

#include "Automaton.h"

class RightParenAutomaton : public Automaton
{
public:
    RightParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //CS236_PROJECT_1_RIGHTPARENAUTOMATON_H
