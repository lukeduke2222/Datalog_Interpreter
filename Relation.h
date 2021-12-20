#ifndef CS236_PROJECT_3_RELATION_H
#define CS236_PROJECT_3_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include "Parameter.h"
#include <string>
#include <set>
#include <iostream>
#include <map>
#include <sstream>

class Relation {
private:
    std::string name;
    Header* header;
    std::set<Tuple> rows;

public:
    Relation(std::string name, std::vector<Parameter*> parameters);

    Relation();

    void setName(const std::string &name);

    void setHeader(Header *header);
    void setHeader(std::vector<std::string> newAttributes);

    void setRows(const std::set<Tuple> newRows);

    std::set<Tuple> getNewRows(std::vector<unsigned int> indexToRemove);
    std::set<Tuple> getNewRows2(std::vector<unsigned int> indicesProject);


    Header* addHeader(std::vector<Parameter*> parameters);
    Header* addHeader(std::vector<std::string> parameters);

        void addTuple(Tuple tuple);
    std::string toString1();
    std::string toString();


    Relation* select1(unsigned int index1, std::string *constant);
    Relation* select2(unsigned int index1, unsigned int index2);
    Relation* project(std::vector<unsigned int> toProject);
    Relation* project2(std::vector<unsigned int> toProject);
    Relation* rename(std::map<std::string, unsigned int> indicesSeen);
    Relation* rename(std::vector<std::string> indicesSeen);
    unsigned int getRowSize();

    Relation* join(Relation* relationToJoin); // joins relation with relation passed in and returns joined relation
    bool unionResults(Relation* results);

    Header* combineHeaders(Header* firstHeader, Header* secondHeader);
    bool isJoinable(Tuple firstTup, Tuple secondTup ,std::map<std::string, std::vector<unsigned int>> indicesToCheck);
    Tuple combineTuples(Tuple firstTup, Tuple secondTup ,std::vector<std::pair<unsigned int, unsigned int>> sharedHeadIndicies);

    std::vector<std::string> getSharedHeaders(Header* firstHeader, Header* secondHeader);
    std::vector<std::pair<unsigned int,unsigned int>> getSharedHeadersIndices(Header* firstHeader, Header* secondHeader);
    bool find(std::string toFind, std::vector<std::string> toSearch);
    bool findSecond(unsigned int valAtSecond, std::vector<std::pair<unsigned int, unsigned int>> pairToSearch);
    unsigned int getIndex(std::string toFind, std::vector<std::string> toSearch);
    std::string getStringFromIndex(unsigned int index, std::vector<std::string> toSearch);
    Header *getHeader() const;
    std::string getName();

    const std::set<Tuple> &getRows() const;
};



#endif //CS236_PROJECT_3_RELATION_H
