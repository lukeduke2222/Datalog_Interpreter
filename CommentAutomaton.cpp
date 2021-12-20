
#include "CommentAutomaton.h"

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S1(const std::string& input) {
    if (index == (int)input.size()||input[index] == '\n') {

    } else if (input[index] != '|') {
        inputRead++;
        index++;
        S2(input);
    } else if (input[index] == '|'){

    } else {
        Serr();
    }
}

void CommentAutomaton::S2(const std::string& input) {

    if (index == (int)input.size()||input[index] == '\n') {

    } else if (index != (int)input.size()&&input[index] != '\n') {
        inputRead++;
        index++;
        S2(input);
    } else {
        Serr();
    }
}

