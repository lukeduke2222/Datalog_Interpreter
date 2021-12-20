#include "Predicates.h"

std::string Predicates::toString() {
    std::string predicatesString;

    predicatesString = id + "(";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (i+1 == parameters.size()) {
            predicatesString += parameters.at(i)->toString();
        } else {
            predicatesString += parameters.at(i)->toString() + ",";
        }
    }
    predicatesString += ")";

    return predicatesString;
}

void Predicates::addName(std::string id) {
    this->id =id;
}

void Predicates::addParameter(std::string parameter) {
    tmpParameter = new Parameter(parameter);
    parameters.push_back(tmpParameter);
}

void Predicates::clear() {
    parameters.clear();
}

const std::vector<Parameter *> &Predicates::getParameters() const {
    return parameters;
}

const std::string Predicates::getId() const{
    return id;
}

std::string Predicates::getId() {
    return id;
}
