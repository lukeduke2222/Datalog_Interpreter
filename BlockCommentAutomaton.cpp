
#include "BlockCommentAutomaton.h"

void BlockCommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void BlockCommentAutomaton::S1(const std::string& input) {
    if (input[index] == '|') {
        inputRead++;
        index++;
        S2(input);
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S2(const std::string& input) {
    if (index == (int)input.size()) {
        type = TokenType::UNDEFINED;
    } else if (input[index] == '\n') {
        inputRead++;
        newLines++;
        index++;
        S2(input);
    } else if (input[index] != '|') {
        inputRead++;
        index++;
        S2(input);
    } else if (input[index] == '|'){
        inputRead++;
        index++;
        S3(input);
    } else {
        Serr();
    }
}

void BlockCommentAutomaton::S3(const std::string& input) {
    if (index == (int)input.size()) {
        type = TokenType::UNDEFINED;
    }
    else if (input[index] == '\n') {
        inputRead++;
        newLines++;
        index++;
        S2(input);
    } else if (input[index] != '#') {
        inputRead++;
        index++;
        S2(input);
    } else if (input[index] == '#'){
        inputRead++;
    } else {
        Serr();
    }
}

