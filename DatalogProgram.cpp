#include "DatalogProgram.h"

void DatalogProgram::toString() {
    std::cout << "Schemes(" << schemes.size() << "):" << std::endl;
    for (unsigned int i = 0; i < schemes.size(); i++) {
        std::cout << "  " << schemes.at(i)->toString() << std::endl;
    }
    std::cout << "Facts(" << facts.size() << "):" << std::endl;
    for (unsigned int i = 0; i < facts.size(); i++) {
        for (unsigned int j = 0; j < facts.at(i)->getParameters().size(); j++) {
            domain.insert(facts.at(i)->getParameters().at(j)->toString());
        }
        std::cout << "  " << facts.at(i)->toString() << "." << std::endl;
    }
    std::cout << "Rules(" << rules.size() << "):" << std::endl;
    for (unsigned int i = 0; i < rules.size(); i++) {
        std::cout << "  " << rules.at(i)->toString() << "." << std::endl;
    }
    std::cout << "Queries(" << queries.size() << "):" << std::endl;
    for (unsigned int i = 0; i < queries.size(); i++) {
        std::cout << "  " << queries.at(i)->toString() << "?" << std::endl;
    }
    std::cout << "Domain(" << domain.size() << "):" << std::endl;
    for (auto elem : domain) {
        std::cout << "  " << elem << std::endl;
    }
}

void DatalogProgram::addScheme(Predicates* predicate) {
    schemes.push_back(predicate);

}

void DatalogProgram::addFact(Predicates* predicate) {
    facts.push_back(predicate);
}

void DatalogProgram::addRule(Rules* rule) {
    rules.push_back(rule);
}

void DatalogProgram::addQuery(Predicates* predicate) {
    queries.push_back(predicate);
}

std::vector<Predicates*>  DatalogProgram::GetSchemes() {
    return schemes;
}

std::vector<Predicates*>  DatalogProgram::GetFacts() {
    return facts;
}

std::vector<Predicates*>  DatalogProgram::GetQueries() {
    return queries;
}

std::vector<Rules*>  DatalogProgram::GetRules() {
    return rules;
}
