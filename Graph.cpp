#include "Graph.h"

Graph::Graph(std::vector<Rules*> rulesToFill) {
    for (unsigned int i = 0; i < rulesToFill.size(); i++) {
        this->rules.push_back(rulesToFill.at(i));
    }
}


void Graph::makeForwardGraph() {
    for (unsigned int i = 0; i < rules.size(); ++i) { // fill map with values
        std::vector<Predicates> body = rules.at(i)->getBodyPredicates();
        Predicates head = rules.at(i)->getHeadPredicate();
        std::set<int> dependencies;
        for (unsigned int j = 0; j < body.size(); ++j) {
            std::set<int> matchedWithHeads;
            matchedWithHeads = findMatchesInHeads(body.at(j).getId());
            dependencies = mergeSets(dependencies, matchedWithHeads);
        }
        std::pair<std::set<int>, bool> value;
        value.first = dependencies;
        value.second = false;
        nodes.insert({i, value});
    }
}

void Graph::makeBackwardGraph() {
    for (unsigned int i = 0; i < rules.size(); ++i) { // fill map with values
        std::vector<Predicates> body = rules.at(i)->getBodyPredicates();
        Predicates head = rules.at(i)->getHeadPredicate();
        std::set<int> dependencies = findMatchesInBodies(head.getId());

        std::pair<std::set<int>, bool> value;
        value.first = dependencies;
        value.second = false;
        nodes.insert({i, value});
    }
}

std::vector<int> Graph::makePostOrderList() {
    for (unsigned int i = 0; i < nodes.size(); ++i) { //set all visited status to false
        nodes[i].second = false;
    }
    for (unsigned int i = 0; i < stack.size(); ++i) { //clears stack
        stack.pop();
    }
    postOrder.clear();
    if (nodes.empty()) { // if no rules in nodes return
        return postOrder;
    }
    RecursiveForest(0); // starting point for DFSForest
    bool anyUnvisited;
    do {
        anyUnvisited = false;
        int ruleToRun;
        for (unsigned int i = 0; i < nodes.size(); ++i) {
            if (!nodes[i].second) {
                anyUnvisited = true;
                ruleToRun = i;
                break;
            }
        }
        if (anyUnvisited) {
            RecursiveForest(ruleToRun);
        }
    } while (anyUnvisited) ;


    return postOrder;
}

void Graph::RecursiveForest(int currRule) {
    nodes[currRule].second = true;
    stack.push(currRule);
    std::set<int> pointsAtRule = nodes[currRule].first;
    if (!pointsAtRule.empty()) {
        for (auto i: pointsAtRule) {
            if(!nodes[i].second) {
                RecursiveForest(i);
            }
        }
        postOrder.push_back(stack.top());
        stack.pop();
    } else {
        postOrder.push_back(stack.top());
        stack.pop();
    }
}

std::vector<std::set<int>> Graph::makeSCCs(std::vector<int> postOrderList) {
    for (unsigned int i = 0; i < nodes.size(); ++i) { //set all visited status to false
        nodes[i].second = false;
    }
    for (unsigned int i = 0; i < stack.size(); ++i) { //clears stack
        stack.pop();
    }

    std::vector<int> reversedPOL = reversePostOrderList(postOrderList);
    std::vector<std::set<int>> SCCs;

    for (unsigned int i = 0; i < reversedPOL.size(); ++i) {
        if (!nodes[reversedPOL.at(i)].second) {
            SCC.clear();
            makeSCC(reversedPOL.at(i));
            SCCs.push_back(SCC);
        }
    }

    SCC.clear();
    return SCCs;
}

void Graph::makeSCC(int currRule) {
    nodes[currRule].second = true;
    stack.push(currRule);
    std::set<int> pointsAtRule = nodes[currRule].first;
    if (!pointsAtRule.empty()) {
        for (auto i: pointsAtRule) {
            if(!nodes[i].second) {
                makeSCC(i);
            }
        }
        SCC.insert(stack.top());
        stack.pop();

    } else {
        SCC.insert(stack.top());
        stack.pop();
    }
}


std::vector<int> Graph::reversePostOrderList(std::vector<int> postOrderList) {
//    reverse(postOrderList.begin(), postOrderList.end()); //reverses post order // because pass server hates this for some reason
//    return postOrderList;

    std::vector<int> reversedList;
//    std::cout << "Post Order List: ";
//    for (unsigned int i = 0; i < postOrderList.size(); ++i) {
//        std::cout << postOrderList.at(i) << "' ";
//    }
//    std::cout << std::endl;

    for (int i = postOrderList.size()-1; i >= 0 ; i--) {
        reversedList.push_back(postOrderList.at(i));
//        std::cout << "i is " << i << std::endl;
//        std::cout << "Reversed Post Order List: ";
//        for (unsigned int j = 0; j < reversedList.size(); ++j) {
//            std::cout << reversedList.at(j) << "' ";
//        }
//        std::cout << std::endl;
    }


    return reversedList;

}

std::set<int> Graph::mergeSets(std::set<int> set1, std::set<int> set2) {
    std::set<int> combinedSet = set1;
    for(auto i: set2) {
        combinedSet.insert(i);
    }
    return combinedSet;
}


std::set<int> Graph::findMatchesInHeads(std::string bodyID) {
    std::set<int> matchedValues;
    for (unsigned int i = 0; i < rules.size(); ++i) {
        if (rules.at(i)->getHeadPredicate().getId() == bodyID) {
            matchedValues.insert(i);
        }

    }
    return matchedValues;
}

std::set<int> Graph::findMatchesInBodies(std::string headID) {
    std::set<int> matchedValues;
    for (unsigned int i = 0; i < rules.size(); ++i) {
        std::vector<Predicates> body = rules.at(i)->getBodyPredicates();
        for (unsigned int j = 0; j < body.size(); ++j) {
            if (body.at(j).getId() == headID) {
                matchedValues.insert(i);
            }
        }
    }
    return matchedValues;
}

std::string Graph::toString() {
    std::stringstream str;
    for (unsigned int i = 0; i < nodes.size(); ++i) {
        std::set<int> values = nodes[i].first;
        str << "R" << i << ":";

        unsigned int itr = 0;
        for (auto s: values) {
            if (itr+1 == values.size()) {
                str << "R" << s;
            } else {
                str << "R" << s << ",";
            }
            itr++;
        }
        str << std::endl;
    }
    return str.str();
}
