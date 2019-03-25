//
// Created by revetoon on 3/14/19.
//

#ifndef OBJPARSER_VARIABLE_HH
#define OBJPARSER_VARIABLE_HH


#include <string>

class LVar {
public:
    LVar();

    const bool operator==(const LVar &rhs) const;
    const bool operator==(const std::string &rhs) const;

public:
    std::string name;
    double value;
};


#endif //OBJPARSER_VARIABLE_HH
