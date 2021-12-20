
#ifndef CS236_PROJECT_2_EOFAUTOMATON_H
#define CS236_PROJECT_2_EOFAUTOMATON_H


#include "Automaton.h"

class EofAutomaton : public Automaton
{
private:



public:
    EofAutomaton() : Automaton(TokenType::END_OF_FILE) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //CS236_PROJECT_1_EOFAUTOMATON_H
