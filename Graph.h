#ifndef DATALOG_INTERPRETER_GRAPH_H
#define DATALOG_INTERPRETER_GRAPH_H

#include "Rules.h"
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <stack>
#include <iostream>



class Graph {
private:
    std::map<int, std::pair<std::set<int>, bool>> nodes;
    std::vector<Rules*> rules;
    std::stack<int> stack;
    std::vector<int> postOrder;
    std::set<int> SCC;
public:
    Graph(std::vector<Rules*> rulesToFill);
    void makeForwardGraph();
    void makeBackwardGraph();
    std::vector<int> makePostOrderList();
    void RecursiveForest(int currRule);
    std::vector<std::set<int>> makeSCCs(std::vector<int> postOrderList);
    std::vector<int> reversePostOrderList(std::vector<int> postOrderList);
    void makeSCC(int currRule);

    std::string toString();

    std::set<int> mergeSets(std::set<int> set1, std::set<int> set2);
    std::set<int> findMatchesInHeads(std::string bodyID);
    std::set<int> findMatchesInBodies(std::string headID);
};


#endif //DATALOG_INTERPRETER_GRAPH_H
