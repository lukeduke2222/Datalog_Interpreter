#include "Rules.h"

std::string Rules::toString() {
    std::string rulesString;

    rulesString = headPredicate.toString() + " :- ";
    for (unsigned int i = 0; i < bodyPredicates.size(); i++) {
        if (i+1 == bodyPredicates.size()) {
            rulesString += bodyPredicates.at(i).toString();
        } else {
            rulesString += bodyPredicates.at(i).toString() + ",";
        }
    }
    return rulesString;
}

void Rules::addHead(Predicates predicate) {
    headPredicate = predicate;
}
void Rules::addBody(Predicates predicate) {
    bodyPredicates.push_back(predicate);
}

const std::vector<Predicates> &Rules::getBodyPredicates() const {
    return bodyPredicates;
}

const Predicates &Rules::getHeadPredicate() const {
    return headPredicate;
}
