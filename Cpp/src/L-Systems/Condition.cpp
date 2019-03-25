//
// Created by revetoon on 3/14/19.
//

#include <sstream>
#include "Condition.hh"

Condition::Condition(const std::string &left, bool (*comparator)(double, double), const std::string &right)
        : left(left), comparator(comparator), right(right) {}

const bool Condition::fulfilled(const Environment &env) {

    double d1;
    try {
        d1 = string_to_double(left);
    } catch (const std::exception &unused) {
        d1 = env.get(left);
    }

    double d2;
    try {
        d2 = string_to_double(right);
    } catch (const std::exception &unused) {
        d2 = env.get(right);
    }

    return comparator(d1, d2);
}

const double Condition::string_to_double(const std::string &s) {
    std::istringstream i(s);
    double x;
    if (!(i >> x))
        throw std::domain_error("could not convert");
    return x;
}

Condition::compFunc Condition::genCompFunc(const std::string &str) {
    if (str == "<") {
        return [](double d1, double d2) -> bool {
            return d1 < d2;
        };
    } else if (str == "<=") {
        return [](double d1, double d2) -> bool {
            return d1 <= d2;
        };
    } else if (str == ">") {
        return [](double d1, double d2) -> bool {
            return d1 > d2;
        };
    } else if (str == ">=") {
        return [](double d1, double d2) -> bool {
            return d1 >= d2;
        };
    } else if (str == "==") {
        return [](double d1, double d2) -> bool {
            return d1 == d2;
        };
    } else if (str == "!=") {
        return [](double d1, double d2) -> bool {
            return d1 != d2;
        };
    }
    return nullptr;
}
