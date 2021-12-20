#ifndef CS236_PROJECT_2_PARSER_H
#define CS236_PROJECT_2_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <iostream>

class Parser {
private:
    std::vector<Token*> dataTokens;
    unsigned int currToken = 0;
    DatalogProgram addToDatalog;
    Predicates* tmpPredicate = nullptr;
    Predicates rulePredicate;
    Rules* tmpRule = nullptr;

public:
    Parser(std::vector<Token*> token);
    ~Parser();
    void Parse();
    void ParseDatalog();
    void scheme();
    void schemeList();
    void factList();
    void fact();
    void stringList();
    void rulesList();
    void rule();
    std::vector<Predicates*> GetDatalogSchemes();
    std::vector<Predicates*> GetDatalogFacts();
    std::vector<Predicates*> GetDatalogQueries();
    std::vector<Rules*> GetDatalogRules();

    Predicates headPredicate();
    Predicates predicate();
    Predicates* queryPredicate();

    void predicateList();
    std::string parameter();
    void parameterList();

    void query();
    void queryList();

    void idList();
    void Match(TokenType);

    };



#endif //CS236_PROJECT_2_PARSER_H
