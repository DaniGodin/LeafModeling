//
// Created by revetoon on 3/6/19.
//

#include "LRuleBasic.hh"


LRuleBasic::LRuleBasic(const std::vector<LNode> &start, const std::vector<LNode> &finish)
        : start(start), finish(finish) {}


std::vector<LNode> LRuleBasic::getResult() {
    return finish;
}

bool LRuleBasic::accept(std::vector<LNode>::iterator it) {
    return vectCmp(it, start.begin(), start.size());
}

