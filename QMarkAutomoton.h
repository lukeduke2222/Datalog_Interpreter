
#ifndef CS236_PROJECT_2_QMARKAUTOMOTON_H
#define CS236_PROJECT_2_QMARKAUTOMOTON_H

#include "Automaton.h"

class QMarkAutomaton : public Automaton
{
public:
    QMarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};
#endif //CS236_PROJECT_1_QMARKAUTOMOTON_H
