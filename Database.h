#ifndef CS236_PROJECT_3_DATABASE_H
#define CS236_PROJECT_3_DATABASE_H

#include "Relation.h"
#include "Predicates.h"
#include <map>
#include <string>


class Database {
private:
    std::map<std::string, Relation*> relations;
public:
    Database(std::vector<Predicates*> schemes, std::vector<Predicates*> facts);

    void addRelation (Relation* relation, std::string id);
    void addRow(std::string name, std::vector<Parameter*> parameters);


    Relation* getRelation(std::string name);
    void printRelations();
    // AddName

};



#endif //CS236_PROJECT_3_DATABASE_H
