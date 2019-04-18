//
// Created by revetoon on 3/14/19.
//

#include "LVar.hh"

LVar::LVar() {}

const bool LVar::operator==(const std::string &rhs) const {
    return rhs == name;
}

const bool LVar::operator==(const LVar &rhs) const {
    return (rhs.name == name);
}

LVar::LVar(const std::string &name, double value) : name(name), value(value) {}


