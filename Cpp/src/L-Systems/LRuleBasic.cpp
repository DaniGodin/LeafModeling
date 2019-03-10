//
// Created by revetoon on 3/6/19.
//

#include "LRuleBasic.hh"


LRuleBasic::LRuleBasic(const std::vector<LNode> &start, const std::vector<LNode> &finish)
        : LRule(start), finish(finish) {}


std::vector<LNode> LRuleBasic::getResult() {
    return finish;
}

