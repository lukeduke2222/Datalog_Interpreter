#include "Interpreter.h"

Interpreter::Interpreter(std::vector<Predicates*> schemes, std::vector<Predicates*> facts, std::vector<Predicates*> queries, std::vector<Rules*> rules) {
    {
        for (unsigned int i = 0; i < schemes.size(); i++) {
            this->schemes.push_back(schemes.at(i));
        }
        for (unsigned int i = 0; i < facts.size(); i++) {
            this->facts.push_back(facts.at(i));
        }
        for (unsigned int i = 0; i < queries.size(); i++) {
            this->queries.push_back(queries.at(i));
        }
        for (unsigned int i = 0; i < rules.size(); i++) {
            this->rules.push_back(rules.at(i));
        }
    }
}

void Interpreter::Interpret() {
    database = new Database(schemes, facts); //making relations

    Graph* forwardGraph = new Graph(rules);
    forwardGraph->makeForwardGraph();
    std::cout << "Dependency Graph" << std::endl;
    std::cout << forwardGraph->toString() << std::endl;

    Graph* backwardGraph = new Graph(rules);
    backwardGraph->makeBackwardGraph();
//    std::cout << "Reverse Graph" << std::endl;
//    std::cout << backwardGraph->toString() << std::endl;

    std::vector<int> postOrderList = backwardGraph->makePostOrderList();
//    std::cout << "Post Order List: ";
//    for (unsigned int i = 0; i < postOrderList.size(); ++i) {
//        std::cout << postOrderList.at(i) << "' ";
//    }
//    std::cout << std::endl;

    std::vector<std::set<int>> SCCs; //strongly connected components
    SCCs = forwardGraph->makeSCCs(postOrderList);


    //start to evaluating rules
    std::cout << "Rule Evaluation" << std::endl;
    for (unsigned int i = 0; i < SCCs.size(); ++i) {
        std::set<int> ruleIndicies = SCCs.at(i);
        std::vector<Rules*> coorelatedRules = getVecOfCoorelatedRules(ruleIndicies);

        bool runOnce = false;

        //check if SCC is 1 and does not loop itself
        if (coorelatedRules.size() == 1) {
            bool pass = true;
            //== 1 && coorelatedRules.at(0)->getHeadPredicate().getId() != coorelatedRules.at(0)->getBodyPredicates().at(0).getId()
            std::vector<Predicates> bodyPreds = coorelatedRules.at(0)->getBodyPredicates();
            Predicates head = coorelatedRules.at(0)->getHeadPredicate();
            for (unsigned int j = 0; j < bodyPreds.size(); ++j) {
                if (bodyPreds.at(j).getId() == head.getId()) {
                    pass = false;
                }
            }
            if (pass) {
                runOnce = true;
            }

        }

        unsigned int itr = 0;
        std::cout << "SCC: ";
        for (auto s: SCCs.at(i)) {
            if (itr+1 == SCCs.at(i).size()) {
                std::cout << "R" << s;
            } else {
                std::cout << "R" << s << "," ;
            }
            itr++;
        }
        std::cout << std::endl;

        bool rulesFullyProcessed = true;
        unsigned int numIterationsOfRules = 0;
        do {
            rulesFullyProcessed = true;
            numIterationsOfRules += 1;
            for (unsigned int i = 0; i < coorelatedRules.size(); ++i) {
                //var that gets current rules
                Relation* results;
                std::vector<Predicates> bodyPredicates = coorelatedRules.at(i)->getBodyPredicates();
                Predicates headPredicate = coorelatedRules.at(i)->getHeadPredicate();
                for (unsigned int j = 0; j < bodyPredicates.size(); ++j) {
                    if (j == 0) {
                        results = evaluatePredicate(bodyPredicates.at(j));
                    } else {
                        results = results->join(evaluatePredicate(bodyPredicates.at(j)));
                    }
                }

                //std::cout << "result before project " << std::endl <<  results->toString() << std::endl;
                std::vector<Parameter*> headParameters = headPredicate.getParameters();
                std::vector<unsigned int> headerToProject;
                for (unsigned int j = 0; j < headParameters.size(); ++j) { // for each head header find its index in the result header
                    headerToProject.push_back( //push back index of header to keep
                            results->getIndex(headParameters.at(j)->toString(), results->getHeader()->getAttributes()));
                }
                results = results->project2(headerToProject); //project filled result
                //std::cout << "result after project " << std::endl <<  results->toString() << std::endl;

                std::vector<std::string> headerToRename = database->getRelation(coorelatedRules.at(i)->getHeadPredicate().getId())->getHeader()->getAttributes();

                results = results->rename(headerToRename);
                //std::cout << "result after rename " << std::endl <<  results->toString() << std::endl;

                bool anyChanges = false;
                std::cout << coorelatedRules.at(i)->toString() << "." << std::endl;
                anyChanges = database->getRelation(coorelatedRules.at(i)->getHeadPredicate().getId())->unionResults(results);
                if (anyChanges) {
                    rulesFullyProcessed = false;
                }
                //std::cout << "result after union " << std::endl <<  database->getRelation(rules.at(i)->getHeadPredicate().getId())->toString() << std::endl;
            }
        } while (!rulesFullyProcessed && !runOnce);

        std::cout << numIterationsOfRules << " passes: ";
        unsigned int itr1 = 0;
        for (auto s: SCCs.at(i)) {
            if (itr1+1 == SCCs.at(i).size()) {
                std::cout << "R" << s;
            } else {
                std::cout << "R" << s << "," ;
            }
            itr1++;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;


    std::cout << "Query Evaluation" << std::endl;
    for (unsigned int i = 0; i < queries.size(); ++i) {
        //std::cout << "run evaluatePredicate "<< i << std::endl;
        parseQuery(queries.at(i));
    }
}
void Interpreter::parseQuery (Predicates* query) {
    //match query with relation and make copy relation and edit that relation with project ect...
    passQuery = false;
    Relation* relation =  evaluatePredicate(query);
    std::cout << query->toString() << "? ";
    if (passQuery) {
        std::cout << "Yes(" << relation->getRowSize() << ")" << std::endl;
        std::cout << relation->toString1();
    } else {
        std::cout << "No" << std::endl;
    }
}

Relation* Interpreter::evaluatePredicate(Predicates* predicate) {
    std::vector<Parameter*> parameters = predicate->getParameters();
    //std::cout << "in evaluatePredicate" << std::endl;

    std::string currName = predicate->getId();
    Relation* currRelation = database->getRelation(currName);
    //std::cout << currRelation->toString() << std::endl;

    std::vector<unsigned int> indicesProject;

    std::map<std::string, unsigned int> indicesSeen;
    std::vector<std::string> valuesToRename;
    std::vector<std::string> renameValues;

    for (unsigned int i = 0; i < parameters.size(); ++i) {
        Parameter* currParameter = parameters.at(i);
        if (currParameter->isConstant()) {
            std::string pointConstant = currParameter->toString();
            currRelation = currRelation->select1(i, &pointConstant);
            //currRelation = currRelation->select1(i, "b");
        } else {
            if (indicesSeen.find(currParameter->toString()) != indicesSeen.end()) {
                //currRelation = currRelation->select2(i, indicesSeen.at(currParameter->toString())); // change to location of first time i saw variable
                currRelation = currRelation->select2(i, indicesSeen[currParameter->toString()]); // change to location of first time i saw variable
            } else {
                indicesProject.push_back(i);
                indicesSeen.insert({currParameter->toString(),i});
                valuesToRename.push_back(currParameter->toString());
                renameValues.push_back(currParameter->toString());
            }
        }
    }
    if (currRelation->getRowSize() > 0) {
        passQuery = true;
    }

    //std::cout << "after selects " << std::endl <<  currRelation->toString() << std::endl;
    currRelation = currRelation->project2(indicesProject);
    //std::cout << "after project " << std::endl <<  currRelation->toString() << std::endl;
    //currRelation = currRelation->rename(indicesSeen);
    currRelation = currRelation->rename(valuesToRename);
    //std::cout << "after rename " << std::endl <<  currRelation->toString() << std::endl;

    return currRelation;
}

Relation* Interpreter::evaluatePredicate(Predicates predicate) {
    std::vector<Parameter*> parameters = predicate.getParameters();

    std::string currName = predicate.getId();
    Relation* currRelation = database->getRelation(currName);

    std::vector<unsigned int> indicesProject;

    std::map<std::string, unsigned int> indicesSeen;
    std::vector<std::string> valuesToRename;
    std::vector<std::string> renameValues;

    for (unsigned int i = 0; i < parameters.size(); ++i) {
        Parameter* currParameter = parameters.at(i);
        if (currParameter->isConstant()) {
            std::string pointConstant = currParameter->toString();
            currRelation = currRelation->select1(i, &pointConstant);
        } else {
            if (indicesSeen.find(currParameter->toString()) != indicesSeen.end()) {
                currRelation = currRelation->select2(i, indicesSeen[currParameter->toString()]); // change to location of first time i saw variable
            } else {
                indicesProject.push_back(i);
                indicesSeen.insert({currParameter->toString(),i});
                valuesToRename.push_back(currParameter->toString());
                renameValues.push_back(currParameter->toString());
            }
        }
    }
    if (currRelation->getRowSize() > 0) {
        passQuery = true;
    }
    currRelation = currRelation->project2(indicesProject);
    currRelation = currRelation->rename(valuesToRename);

    return currRelation;
}

std::vector<Rules*> Interpreter::getVecOfCoorelatedRules(std::set<int> rulesIndices) {
    std::vector<Rules*> rulesVec;
    for (auto i: rulesIndices) {
        rulesVec.push_back(rules.at(i));
    }
    return rulesVec;
}