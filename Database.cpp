#include "Database.h"


Database::Database(std::vector<Predicates*> schemes, std::vector<Predicates*> facts) {
    for (unsigned int i = 0; i < schemes.size(); i++) {
        Relation* relation = new Relation(schemes.at(i)->getId(), schemes.at(i)->getParameters());
        std::string id = schemes.at(i)->getId();
        addRelation(relation, id);
    }
    for (unsigned int i = 0; i < facts.size(); i++) {
        for(std::pair<std::string, Relation*> currentPair : relations) {
            if(facts.at(i)->getId() == currentPair.first) {
                addRow(currentPair.first, facts.at(i)->getParameters());
            }
        }
    }
}


void Database::addRelation(Relation* relation, std::string id) {
    relations.insert({id, relation});
}

void Database::addRow(std::string name, std::vector<Parameter*> parameters) {
    Tuple tuple =  Tuple(parameters);
    relations[name]->addTuple(tuple);
}

void Database::printRelations() {
    for(std::pair<std::string, Relation*> currentPair : relations) {
        std::cout << currentPair.first << std::endl;
        std::cout << currentPair.second->toString() << std::endl;
    }
}

Relation* Database::getRelation(std::string name) {
    Relation* relationToReturn = relations[name];
    return relationToReturn;
}