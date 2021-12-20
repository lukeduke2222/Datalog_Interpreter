#include "Relation.h"

Relation::Relation() {}

Relation::Relation(std::string name, std::vector<Parameter*> parameters) {
    this->name = name;
    this->header = addHeader(parameters);
}

void Relation::setName(const std::string &name) {
    Relation::name = name;
}

void Relation::setHeader(Header *header) {
    Relation::header = header;
}
void Relation::setHeader(std::vector<std::string> newAttributes) {
    this->header = addHeader(newAttributes);
}


void Relation::setRows(const std::set<Tuple> newRows) {
    Relation::rows = newRows;
}


void Relation::addTuple(Tuple tuple) {
   rows.insert(tuple);
}

std::string Relation::toString() {
    std::string str = "";
    str += header->toString() + "\n";
    for(Tuple t : rows) {
        str += t.toString() + "\n";
    }
    return str;
}
std::string Relation::toString1() {
    std::vector<std::string> rowValues;
    std::vector<std::string> headerValues = header->getAttributes();
    std::stringstream ss;
    std::string str = "";
    bool newLine = false;
    for (Tuple t: rows) {
        rowValues = t.getValues();
        for (unsigned int i = 0; i < rowValues.size(); ++i) {
            if (i+1 == rowValues.size()) {
                std::cout << "  " << headerValues.at(i) << "=" << rowValues.at(i);
                newLine = true;
            } else {
                std::cout << "  " << headerValues.at(i) << "=" << rowValues.at(i) << ",";
                newLine = true;
            }
        }
        if (newLine) {
            std::cout << std::endl;
        }
    }
    return str;
}

Header* Relation::addHeader(std::vector<Parameter*> parameters) {
    Header* header = new Header(parameters);
    return header;
}
Header* Relation::addHeader(std::vector<std::string> parameters) {
    Header* header = new Header(parameters);
    return header;
}



Relation* Relation::select1(unsigned int index1, std::string* constant) {
    std::set<Tuple> newTuples;
    for (Tuple t : rows) {
        if (t.getValue(index1) == *constant) {
            newTuples.insert(t);
        }
    }
    Relation* relation = new Relation();
    relation->setRows(newTuples);
    relation->setName(name);
    relation->setHeader(header);
    return relation;
}



Relation* Relation::select2(unsigned int index1, unsigned int index2) {
    std::set<Tuple> newTuples;
    for (Tuple t : rows) {
        if (t.getValue(index1) == t.getValue(index2)) {
            newTuples.insert(t);
        }
    }
    Relation* relation = new Relation();
    relation->setRows(newTuples);
    relation->setName(name);
    relation->setHeader(header);
    return relation;
}

Relation* Relation::project(std::vector<unsigned int> indicesProject) {
    std::vector<std::string> columnsToKeep;
    std::vector<unsigned int> columnsToRemove;
    //std::cout << "made it to project" << std::endl;

    //std::cout << "what to project" << std::endl;
//    for (unsigned int i = 0; i < indicesProject.size(); ++i) {
//        std::cout << indicesProject.at(i);
//    }
    //std::cout << std::endl;

    std::set<Tuple> newTuples;

    std::vector<std::string> headerAttributes =  header->getAttributes();
    //unsigned int rowLength = headerAttributes.size();

    unsigned int indexCount = 0;

    for (unsigned int i = 0; i < headerAttributes.size(); i++) {
        if (indicesProject.size() > indexCount) {
            if (i == indicesProject.at(indexCount)) { //134
                columnsToKeep.push_back(headerAttributes.at(i));
                indexCount++;
            } else {
                columnsToRemove.push_back(i);
            }
        } else {
            columnsToRemove.push_back(i);
        }
    }

//    std::cout << "what to remove" << std::endl;
//    for (unsigned int i = 0; i < columnsToRemove.size(); ++i) {
//        std::cout << columnsToRemove.at(i);
//    }
//    std::cout << std::endl;

    Relation* relation = new Relation();
    newTuples = getNewRows(columnsToRemove);
    relation->setRows(newTuples); //  how to keep certain rows
    relation->setName(name);
    relation->setHeader(columnsToKeep);

    return relation;
}

Relation* Relation::project2(std::vector<unsigned int> indicesProject) {
    std::vector<std::string> headerAttributes = this->header->getAttributes();
    std::vector<std::string> newHeaderAttributes;

    for (unsigned int i = 0; i < indicesProject.size(); ++i) {
        newHeaderAttributes.push_back(getStringFromIndex(indicesProject.at(i), headerAttributes));
    }

    std::set<Tuple> newTuples;
    newTuples = getNewRows2(indicesProject);

    Relation* relation = new Relation();
    relation->setRows(newTuples); //  how to keep certain rows
    relation->setName(name);
    relation->setHeader(newHeaderAttributes);

    return relation;
}

std::set<Tuple> Relation::getNewRows2(std::vector<unsigned int> indicesProject) {
    std::set<Tuple> newRows;
    std::vector<std::string> newValues;

    for (Tuple t: rows) {
        std::vector<std::string> oldValues = t.getValues();
        for (unsigned int i = 0; i < indicesProject.size(); ++i) {
            newValues.push_back(getStringFromIndex(indicesProject.at(i), oldValues));
        }
        Tuple tuple = Tuple(newValues);
        newRows.insert(tuple);
        newValues.clear();
    }

    return newRows;
}

std::set<Tuple> Relation::getNewRows(std::vector<unsigned int> indexToRemove) {
    std::set<Tuple> newRows;
    std::vector<unsigned int> toRemove = indexToRemove;
    std::vector<std::string> values;
    std::vector<std::string> newValues;
    //unsigned int count;

    unsigned int indexCounter= 0;

    if (toRemove.size() == 0) {
        return rows;
    } else {
        for (Tuple t: rows) {
            toRemove = indexToRemove;
            values = t.getValues();
            //count =  toRemove.size();
            for (unsigned int i = 0; i < values.size(); ++i) {
                if (toRemove.size() > 0) {
                    //count >=  indexCounter
                    if (i == toRemove.at(0)) {
                        toRemove.erase(toRemove.begin());
                        //i--;
                        indexCounter++;
                        //count--;
                    } else {
                        newValues.push_back(values.at(i));
                        indexCounter++;
                    }
                } else if (toRemove.size() == 0 && indexCounter != values.size()) {
                    newValues.push_back(values.at(i));
                    indexCounter++;
                }
            }
            Tuple tuple = Tuple(newValues);
            newRows.insert(tuple);
            indexCounter = 0;
            newValues.clear();
        }
        return newRows;
    }
}


Relation* Relation::rename(std::vector<std::string> indicesSeen) {
    std::vector<std::string> attributes = header->getAttributes();

    for (unsigned int i = 0; i < indicesSeen.size(); ++i) {
        attributes.at(i) = indicesSeen.at(i);
    }

    Relation* relation = new Relation();
    relation->setRows(rows); //  how to keep certain rows
    relation->setName(name);
    relation->setHeader(attributes);

    return relation;
}

unsigned int Relation::getRowSize() {
    return rows.size();
}

Relation* Relation::join(Relation *relationToJoin) {
    Header* combinedHeader = combineHeaders(this->header, relationToJoin->header);
    std::vector<std::pair<unsigned int, unsigned int>> sharedHeadIndicies = getSharedHeadersIndices(this->header, relationToJoin->header);
    std::vector<std::string> sharedHeaders = getSharedHeaders(this->header, relationToJoin->header);
    std::map<std::string, std::vector<unsigned int>> indicesToCheck; //makes a table of shared headers and their index locations

    if (!sharedHeaders.empty()) { //populates indicesToCheck with the shared headers and their indices
        std::vector<unsigned int> indices;
        for (unsigned int i = 0; i < sharedHeaders.size(); ++i) {
            indices.clear();
            indices.push_back(getIndex(sharedHeaders.at(i), this->header->getAttributes()));
            indices.push_back(getIndex(sharedHeaders.at(i), relationToJoin->header->getAttributes()));
            indicesToCheck[sharedHeaders.at(i)] = indices;
        }
    }

    //begin to populate with new Tuples
    std::set<Tuple> newRows;
    for (Tuple localRow: this->rows) {
        for (Tuple toJoinRow: relationToJoin->rows) {
            if (isJoinable(localRow, toJoinRow, indicesToCheck)) {
                //vector of pairs i want to keep
                newRows.insert(combineTuples(localRow, toJoinRow, sharedHeadIndicies));// where heads match // combine tuples returns the two tuples combined and makes a new Row
            }
        }
    }

    Relation* relation = new Relation();
    relation->setRows(newRows);
    relation->setName(name);
    relation->setHeader(combinedHeader);

    return relation;
}

Header* Relation::combineHeaders(Header* firstHeader, Header* secondHeader) {
    std::vector<std::string> firstHeads = firstHeader->getAttributes();
    std::vector<std::string> secondHeads = secondHeader->getAttributes();
    std::vector<std::string> combinedHeads = firstHeads;

    for (unsigned int i = 0; i < secondHeads.size(); i++) {
        if (!(find(secondHeads.at(i), combinedHeads))) {
            combinedHeads.push_back(secondHeads.at(i));
        }
    }
    Header* combinedHeader = new Header(combinedHeads);
    return combinedHeader;
}

std::vector<std::pair<unsigned int,unsigned int>> Relation::getSharedHeadersIndices(Header* firstHeader, Header* secondHeader) {
    std::vector<std::string> firstHeads = firstHeader->getAttributes();
    std::vector<std::string> secondHeads = secondHeader->getAttributes();
    std::vector<std::pair<unsigned int,unsigned int>> sharedHeadIndices;

    for (unsigned int i = 0; i < secondHeads.size(); i++) {
        if ((find(secondHeads.at(i), firstHeads))) {
            std::pair<unsigned int,unsigned int> val;
            val.first = getIndex(secondHeads.at(i), firstHeads);
            val.second = i;
            sharedHeadIndices.push_back(val);
        }
    }
    return sharedHeadIndices;
}

bool Relation::isJoinable(Tuple firstTup, Tuple secondTup ,std::map<std::string, std::vector<unsigned int>> sharedIndices) {
    std::vector<std::string> firstTupVals = firstTup.getValues();
    std::vector<std::string> secondTupVals = secondTup.getValues();

    for (auto const& x : sharedIndices) { // goes through each map element that each contain indices on headers
        if (firstTupVals.at(x.second.at(0)) != secondTupVals.at(x.second.at(1))) { // if both tuples have same val skip the return false
            return false; //stop and return false
        }
    }
    return true; //if never return false it must be true and the two tuples are joinable
}

Tuple Relation::combineTuples(Tuple firstTup, Tuple secondTup ,std::vector<std::pair<unsigned int, unsigned int>> sharedHeadIndicies) {
    std::vector<std::string> firstTupVals = firstTup.getValues();
    std::vector<std::string> secondTupVals = secondTup.getValues();
    std::vector<std::string> combinedTupVals = firstTupVals;

    for (unsigned int i = 0; i < secondTupVals.size(); ++i) {
        if (!findSecond(i, sharedHeadIndicies)) { // add if not a repeat header
            combinedTupVals.push_back(secondTupVals.at(i));
        }
    }
    Tuple combinedTuple = Tuple(combinedTupVals);
    return combinedTuple;
}


std::vector<std::string> Relation::getSharedHeaders(Header* firstHeader, Header* secondHeader) {
    std::vector<std::string> firstHeads = firstHeader->getAttributes();
    std::vector<std::string> secondHeads = secondHeader->getAttributes();
    std::vector<std::string> sharedHeads;

    for (unsigned int i = 0; i < secondHeads.size(); i++) {
        if (find(secondHeads.at(i), firstHeads)) {
            sharedHeads.push_back(secondHeads.at(i));
        }
    }
    return sharedHeads;
}

bool Relation::unionResults(Relation* result) {
    std::set<Tuple> resultRows = result->getRows();
    std::set<Tuple> updatedRows = getRows(); //fills with current rows
    std::vector<std::string> headAttributes = this->header->getAttributes();

    bool anyChanges = false;

    for (Tuple t: resultRows) {
        if (updatedRows.insert(t).second) {
            std::string str = "";
            for (unsigned int i = 0; i < headAttributes.size(); ++i) {
                if (i+1 == headAttributes.size()) {
                    str += headAttributes.at(i) + "=" + t.toStringAt(i);
                } else {
                    str += headAttributes.at(i) + "=" + t.toStringAt(i) + ", ";
                }
            }
            std::cout << str << std::endl;
            anyChanges = true;
        }
    }
    setRows(updatedRows);
    return anyChanges;
}

unsigned int Relation::getIndex(std::string toFind, std::vector<std::string> toSearch) {
    for (unsigned int i = 0; i < toSearch.size(); i++) {
        if (toFind == toSearch.at(i)) {
            return i;
        }
    }
    return 131; //error has occurred aka. value not in search
}

std::string Relation::getStringFromIndex(unsigned int index, std::vector<std::string> toSearch) {
    return toSearch.at(index);
}

bool Relation::find(std::string toFind, std::vector<std::string> toSearch) {
    for (unsigned int i = 0; i < toSearch.size(); i++) {
        if (toFind == toSearch.at(i)) {
            return true;
        }
    }
    return false;
}

Header *Relation::getHeader() const {
    return header;
}

std::string Relation::getName() {
    return name;
}

const std::set<Tuple> &Relation::getRows() const {
    return rows;
}

bool Relation::findSecond(unsigned int valAtSecond, std::vector<std::pair<unsigned int, unsigned int>> pairToSearch) {
    for (unsigned int i = 0; i < pairToSearch.size(); ++i) {
        if (valAtSecond == pairToSearch.at(i).second) {
            return true;
        }
    }
    return false;
}

