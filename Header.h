#ifndef CS236_PROJECT_3_HEADER_H
#define CS236_PROJECT_3_HEADER_H
#include <vector>
#include "Parameter.h"

class Header {
private:
    std::vector<std::string> attributes;
public:
    Header(std::vector<Parameter *> parameters);
    Header(std::vector<std::string> parameters);
    std::string toString();
    std::vector<std::string> getAttributes();
};



#endif //CS236_PROJECT_3_HEADER_H
