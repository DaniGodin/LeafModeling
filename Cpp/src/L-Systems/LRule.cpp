//
// Created by revetoon on 3/6/19.
//

#include "LRule.hh"

template <>
std::vector<LNode<std::string>> LRule<std::string>::genRule(const std::string &rule) {
    auto res = std::vector<LNode<std::string>>();
    for (unsigned i = 0; i < rule.size(); ++i) {
        res.push_back(LNode<std::string>(rule.substr(i, 1)));
    }
    return res;
}