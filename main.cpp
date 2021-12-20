#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    if (argc < 2) {
        return 1;
    }
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        return 2;
    }
    std::stringstream ss;
    std::string toRun;

    ss << inFile.rdbuf();

    toRun = ss.str();
    lexer->Run(toRun);
    Parser* parser = new Parser(lexer->GetTokens());
    parser->Parse();
    Interpreter* interpreter = new Interpreter(parser->GetDatalogSchemes(),parser->GetDatalogFacts(),parser->GetDatalogQueries(),parser->GetDatalogRules());
    interpreter->Interpret();

    delete lexer;
    return 0;
}
