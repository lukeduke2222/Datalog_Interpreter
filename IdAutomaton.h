
#ifndef CS236_PROJECT_2_IDAUTOMATON_H
#define CS236_PROJECT_2_IDAUTOMATON_H

#include "Automaton.h"

class IdAutomaton : public Automaton
{
private:
    void S1(const std::string& input);

public:
    IdAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //CS236_PROJECT_1_IDAUTOMATON_H
