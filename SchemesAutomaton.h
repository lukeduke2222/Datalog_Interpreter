
#ifndef CS236_PROJECT_2_SCHEMESAUTOMATON_H
#define CS236_PROJECT_2_SCHEMESAUTOMATON_H

#include "Automaton.h"

class SchemesAutomaton : public Automaton
{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);
    void S3(const std::string& input);
    void S4(const std::string& input);
    void S5(const std::string& input);
    void S6(const std::string& input);


public:
    SchemesAutomaton() : Automaton(TokenType::SCHEMES) {}  // Call the base constructor

    void S0(const std::string& input);
};


#endif //CS236_PROJECT_1_SCHEMESAUTOMATON_H
