#include "Header.h"

Header::Header(std::vector<Parameter *> parameters) {
    for (unsigned int i = 0; i < parameters.size(); i++) {
        attributes.push_back(parameters.at(i)->toString());
    }
}
Header::Header(std::vector<std::string> parameters) {
    for (unsigned int i = 0; i < parameters.size(); i++) {
        attributes.push_back(parameters.at(i));
    }
}

std::string Header::toString() {
    std::string str = "";
    for (unsigned int i = 0; i < attributes.size(); ++i) {
        if (i + 1 == attributes.size()) {
            str += attributes.at(i);
        } else {
            str += attributes.at(i) + " ";
        }
    }
    return str;
}

std::vector<std::string> Header::getAttributes() {
    return attributes;
}
