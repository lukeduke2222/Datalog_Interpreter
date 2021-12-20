#ifndef CS236_PROJECT_2_DATALOGPROGRAM_H
#define CS236_PROJECT_2_DATALOGPROGRAM_H

#include "Predicates.h"
#include "Rules.h"
#include <iostream>
#include <vector>
#include <set>
#include <string>

class DatalogProgram {
private:
    std::vector<Predicates*> schemes;
    std::vector<Predicates*> facts;
    std::vector<Predicates*> queries;
    std::vector<Rules*> rules;
    std::set<std::string> domain;


public:
//    DatalogProgram();
//    ~DatalogProgram();

    void addScheme(Predicates* predicate);
    void addFact(Predicates* predicate);
    void addRule(Rules* rule);
    void addQuery(Predicates* predicate);

    std::vector<Predicates*> GetSchemes();
    std::vector<Predicates*> GetFacts();
    std::vector<Predicates*> GetQueries();
    std::vector<Rules*> GetRules();



    void toString();

};




#endif //CS236_PROJECT_2_DATALOGPROGRAM_H
