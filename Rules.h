#ifndef CS236_PROJECT_2_RULES_H
#define CS236_PROJECT_2_RULES_H
#include "Predicates.h"
#include <vector>
#include <string>

class Rules {
private:
    Predicates headPredicate;
    std::vector<Predicates> bodyPredicates;

public:
//    Rules();
//    ~Rules();
    std::string toString();

    const Predicates &getHeadPredicate() const;

    void addHead(Predicates predicate);
    void addBody(Predicates predicate);

    const std::vector<Predicates> &getBodyPredicates() const;
};



#endif //CS236_PROJECT_2_RULES_H
