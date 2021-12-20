#include "Tuple.h"

Tuple::Tuple(std::vector<Parameter*> parameters) {
    for (unsigned int i = 0; i < parameters.size(); ++i) {
        values.push_back(parameters.at(i)->toString());
    }
}
Tuple::Tuple(std::vector<std::string> parameters) {
    for (unsigned int i = 0; i < parameters.size(); ++i) {
        values.push_back(parameters.at(i));
    }
}

std::string Tuple::toString() {
    std::string str = "";

    for (unsigned int i = 0; i < values.size(); ++i) {
        if (i + 1 == values.size()) {
            str += values.at(i);
        } else {
            str += values.at(i) + " ";
        }
    }

    return str;
}

std::string Tuple::toStringAt(unsigned int index) {
    std::string str = "";
    str = values.at(index);
    return str;
}

std::string Tuple::getValue(unsigned int index) {
    return values.at(index);
}

