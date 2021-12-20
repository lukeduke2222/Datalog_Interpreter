
#include "EofAutomaton.h"

void EofAutomaton::S0(const std::string& input) {
    if (index == (int)input.size()) {
        inputRead++;
    }
    else {
        Serr();
    }
}
