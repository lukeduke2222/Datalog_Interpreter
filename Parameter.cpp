#include "Parameter.h"

Parameter::Parameter(std::string parameter) {
    this->p = parameter;
    if (p.at(0) == '\'') {
        isString = true;
    }
}

std::string Parameter::toString() {
    return p;
}

bool Parameter::isConstant() {
    if (isString == true) {
        return true;
    } else {
        return false;
    }
}

