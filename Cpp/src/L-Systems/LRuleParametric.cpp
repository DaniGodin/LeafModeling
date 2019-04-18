//
// Created by revetoon on 3/14/19.
//

#include <sstream>
#include <iostream>
#include "LRuleParametric.hh"


LRuleParametric::LRuleParametric(const std::string &fName, const std::vector<LNode> &finish,
                                 const std::vector<Condition> &cond, int paramCount) : fName(fName), finish(finish),
                                                                                       cond(cond),
                                                                                       paramCount(paramCount) {}

int LRuleParametric::accept(std::vector<LNode> &v, unsigned index, Environment &env) {

    if (strCmp(v[index].getId(), fName, fName.size()) == false)
        return 0;

    for (Condition &c: cond) {
        if (!c.fulfilled(env))
            return 0;
    }

    if (!parseParams(v[index].getId()))
        return 0;

    return 1;
}

std::vector<LNode> LRuleParametric::getResult() {
    return finish;
}

bool LRuleParametric::parseParams(const std::string &s) {
    std::string sstripped = s.substr(0, s.size() - 1);
    std::stringstream ss(sstripped);
    char c;

    while (!ss.eof()) {
        ss >> c;
        if (c == '(')
            break;
    }
    std::string seg;

    params.clear();
    while(std::getline(ss, seg, ','))
    {
        params.push_back(seg);
    }
    if (params.size() != paramCount)
        return false;
    return true;
}

bool LRuleParametric::strCmp(const std::string &lhs, const std::string &rhs, int count) {
    for (unsigned i = 0; i < count; ++i) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}
