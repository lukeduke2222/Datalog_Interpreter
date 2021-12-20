#ifndef CS236_PROJECT_3_TUPLE_H
#define CS236_PROJECT_3_TUPLE_H

#include "Parameter.h"
#include <vector>
#include <string>


class Tuple {
private:
   std::vector<std::string> values;
public:
    Tuple(std::vector<Parameter*> parameters);
    Tuple(std::vector<std::string> parameters);
    std::string toString();
    std::string toStringAt(unsigned int index);
    std::string getValue(unsigned int index);

    bool operator < (const Tuple & other) const {
        return values < other.values;
    }

    std::vector<std::string> getValues() {
        return values;
    }
};



#endif //CS236_PROJECT_3_TUPLE_H
