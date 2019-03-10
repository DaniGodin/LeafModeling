//
// Created by revetoon on 3/6/19.
//

#include <iostream>
#include "LRule.hh"


bool LRule::vectCmp(std::vector<LNode>::iterator lhs, std::vector<LNode>::iterator rhs, unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        if (*lhs != *rhs)
            return false;
        ++lhs;
        ++rhs;
    }
    return true;
}

std::vector<LNode> LRule::genRule(const std::string &rule) {
    auto res = std::vector<LNode>();
    for (unsigned i = 0; i < rule.size(); ++i) {
        res.push_back(LNode(rule.substr(i, 1)));
    }
    return res;
}