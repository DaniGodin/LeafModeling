//
// Created by revetoon on 3/14/19.
//

#include "LRuleParametric.hh"

bool LRuleParametric::accept(std::vector<LNode> &v, unsigned index, Environment &env) {

    std::vector<LNode>::iterator nth = v.begin() + index;
    if (vectCmp(nth, fName.begin(), fName.size()) == false)
        return false;

    for (Condition &c: cond) {
        if (!c.fulfilled(env))
            return false;
    }
    return true;
}

std::vector<LNode> LRuleParametric::getResult() {
    return std::vector<LNode>();
}
