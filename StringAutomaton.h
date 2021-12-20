
#ifndef CS236_PROJECT_2_STRINGAUTOMATON_H
#define CS236_PROJECT_2_STRINGAUTOMATON_H

#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);



public:
    StringAutomaton() : Automaton(TokenType::STRING) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif //CS236_PROJECT_1_STRINGAUTOMATON_H
