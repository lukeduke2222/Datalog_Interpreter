
#include "StringAutomaton.h"
#include <iostream>

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void StringAutomaton::S1(const std::string& input) {
    if (index == (int)input.size()) {
        //std::cout << "hit end of file" << std::endl;
        type = TokenType::UNDEFINED;
    } else if (input[index] == '\n') {
        newLines++;
        inputRead++;
        index++;
        S1(input);
    } else if (input[index] == '\''){
        inputRead++;
        index++;
        S3(input);
    } else if (input[index] != '\'') {
        inputRead++;
        index++;
        S1(input);
    } else {
        Serr();
    }
}

void StringAutomaton::S2(const std::string& input) {

    if (index == (int)input.size()){
        //std::cout << "hit end of file" << std::endl;
        type = TokenType::UNDEFINED;
    }
    else if (input[index] != '\'') {

    } else if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    } else {
        Serr();
    }
}
void StringAutomaton::S3(const std::string& input) {

    if (input[index] != '\''){

    } else if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
