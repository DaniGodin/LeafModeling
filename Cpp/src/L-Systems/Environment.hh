//
// Created by revetoon on 3/14/19.
//

#ifndef OBJPARSER_ENVIRONMENT_HH
#define OBJPARSER_ENVIRONMENT_HH


#include <vector>
#include "LVar.hh"

class Environment {
public:
    Environment();

    const bool exists(const std::string &name);
    const bool isZero(const std::string &name);
    const double get(const std::string &name);
    const double get(const std::string &name) const;
    bool set(const std::string &name, double val);

    Environment &operator+=(const LVar &var);

private:
    LVar &getVar(const std::string &name);
    std::vector<LVar> vars;
};


#endif //OBJPARSER_ENVIRONMENT_HH
