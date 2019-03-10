//
// Created by revetoon on 3/6/19.
//

#include <iostream>
#include "LRule.hh"


LRule::LRule(const std::vector<LNode> &start) :start(start) {}


template<typename It1, typename It2>
bool LRule::vectCmp(It1 lhs, It2 rhs, unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        if (*lhs != *rhs)
            return false;
        ++lhs;
        ++rhs;
    }
    return true;
}

bool LRule::accept(std::vector<LNode>::iterator it) {
    return vectCmp(it, start.begin(), start.size());
}

std::vector<LNode> LRule::getResult() {
    std::cerr << "DO NOT USE" << std::endl;
    return std::vector<LNode>();
}

std::vector<LNode> LRule::genRule(const std::string &rule) {
    auto res = std::vector<LNode>();
    for (unsigned i = 0; i < rule.size(); ++i) {
        res.push_back(LNode(rule.substr(i, 1)));
    }
    return res;
}