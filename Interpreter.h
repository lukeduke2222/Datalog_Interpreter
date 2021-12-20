
#ifndef CS236_PROJECT_3_INTERPRETER_H
#define CS236_PROJECT_3_INTERPRETER_H

#include "Predicates.h"
#include "Rules.h"
#include "Database.h"
#include "Graph.h"
#include <iostream>


class Interpreter {
private:
    Database* database;
    std::vector<Predicates*> schemes;
    std::vector<Predicates*> facts;
    std::vector<Predicates*> queries;
    std::vector<Rules*> rules;

    bool passQuery = false;

public:
    Interpreter(std::vector<Predicates*> schemes, std::vector<Predicates*> facts, std::vector<Predicates*> queries, std::vector<Rules*> rules);
    void Interpret();
    void parseQuery (Predicates* queries);
    Relation* evaluatePredicate(Predicates* predicate);
    Relation* evaluatePredicate(Predicates predicate);

    std::vector<Rules*> getVecOfCoorelatedRules(std::set<int> rulesIndices);

};

#endif //CS236_PROJECT_3_INTERPRETER_H
