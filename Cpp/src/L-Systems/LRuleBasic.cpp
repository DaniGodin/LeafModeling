//
// Created by revetoon on 3/6/19.
//

#include "LRuleBasic.hh"


LRuleBasic::LRuleBasic(const std::vector<LNode> &start, const std::vector<LNode> &finish)
        : start(start), finish(finish) {}


std::vector<LNode> LRuleBasic::getResult() {
    return finish;
}

int LRuleBasic::accept(std::vector<LNode> &v, unsigned index, Environment &env) {
    std::vector<LNode>::iterator nth = v.begin() + index;
    if (!vectCmp(nth, start.begin(), start.size()))
        return false;
    return start.size();
}

