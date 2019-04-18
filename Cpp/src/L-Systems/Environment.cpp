//
// Created by revetoon on 3/14/19.
//

#include <stdexcept>
#include "Environment.hh"

const bool Environment::exists(const std::string &name) {
    try {
        get(name);
    } catch (const std::exception &unused) {
        return false;
    }
    return true;
}

const bool Environment::isZero(const std::string &name) {
    return get(name) == 0;
}

const double Environment::get(const std::string &name) {
    for (const LVar &v : vars) {
        if (v == name)
            return v.value;
    }
    throw std::out_of_range("Element not found."); // error
}

bool Environment::set(const std::string &name, double val) {
    getVar(name).value = val;
    return true;
}

LVar &Environment::getVar(const std::string &name) {
    for (LVar &v : vars) {
        if (v == name)
            return v;
    }
    throw std::out_of_range("Element not found."); // error
}

Environment::Environment() {}

Environment &Environment::operator+=(const LVar &var) {
    vars.push_back(std::move(var));
    return *this;
}

const double Environment::get(const std::string &name) const {
    for (const LVar &v : vars) {
        if (v == name)
            return v.value;
    }
    throw std::out_of_range("Element not found."); // error
}

Environment::Environment(const std::vector<LVar> &vars)
    : vars(vars)
{}
