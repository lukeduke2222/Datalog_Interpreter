#ifndef CS236_PROJECT_2_PARAMETER_H
#define CS236_PROJECT_2_PARAMETER_H
#include <string>

class Parameter {
private:
    std::string p;
    bool isString = false;

public:
    Parameter(std::string parameter);
    ~Parameter();
    std::string toString();
    bool isConstant();

};



#endif //CS236_PROJECT_2_PARAMETER_H
