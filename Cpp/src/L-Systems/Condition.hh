//
// Created by revetoon on 3/14/19.
//

#ifndef OBJPARSER_CONDITION_HH
#define OBJPARSER_CONDITION_HH


#include <string>
#include "Environment.hh"

class Condition {
public:
    typedef bool(*compFunc)(double, double);

public:
    Condition(const std::string &left, bool (*comparator)(double, double), const std::string &right);

    const bool fulfilled(const Environment &env);

    static Condition::compFunc genCompFunc(const std::string &str);

private:
    const double string_to_double(const std::string& s);


private:
    std::string left;
    compFunc comparator;
    std::string right;
};


#endif //OBJPARSER_CONDITION_HH
