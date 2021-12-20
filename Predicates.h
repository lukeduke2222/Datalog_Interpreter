
#ifndef CS236_PROJECT_2_PREDICATES_H
#define CS236_PROJECT_2_PREDICATES_H
#include "Parameter.h"
#include <string>
#include <vector>

class Predicates{
private:
    std::string id;
    std::vector<Parameter*> parameters;
    Parameter* tmpParameter = nullptr;
public:
//    Predicates();
//    ~Predicates();
    std::string toString();
    void addName(std::string id);
    void addParameter(std::string parameter);
    void clear();

    const std::vector<Parameter *> &getParameters() const;
    std::string getId();
    const std::string getId() const;
};

#endif //CS236_PROJECT_2_PREDICATES_H
