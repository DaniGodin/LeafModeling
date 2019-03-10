//
// Created by revetoon on 3/10/19.
//

#include "LRuleContext.hh"
#include <stack>
#include <iostream>

bool LRuleContext::accept(std::vector<LNode> &v, unsigned index) {
    // check if "basic" rule apply
    std::vector<LNode>::iterator nth = v.begin() + index;
    if (!vectCmp(nth, start.begin(), start.size()))
        return false;

    // check the precede
    if (!acceptPrecede(v, index))
        return false;

    // check the follow
    if (!acceptFollow(v, index))
        return false;

    return true;
}

std::vector<LNode> LRuleContext::getResult() {
    return finish;
}

LRuleContext::LRuleContext(const std::vector<LNode> &precede, const std::vector<LNode> &start,
                           const std::vector<LNode> &follow, const std::vector<LNode> &finish) : precede(precede),
                                                                                                 start(start),
                                                                                                 follow(follow),
                                                                                                 finish(finish) {}

LRuleContext::LRuleContext(const std::vector<LNode> &precede, const std::vector<LNode> &start,
                           const std::vector<LNode> &follow, const std::vector<LNode> &finish,
                           const std::vector<LNode> &ignore) : precede(precede), start(start), follow(follow),
                                                               finish(finish), ignore(ignore) {}

bool LRuleContext::vectContains(const std::vector<LNode> &v, const LNode &n) {
    for (const LNode &i : v) {
        if (i.getId() == n.getId())
            return true;
    }
    return false;
}

unsigned LRuleContext::skipToMatchingBracket(std::vector<LNode> &v, int index, bool reverse) {
    int i = reverse ? -1 : 1;
    while (index >= 0 && index < v.size()) {
        if (reverse && v[index].getId() == "[")
            break;
        if (!reverse && v[index].getId() == "]")
            break;
        index += i;
    }
    return index;
}

bool LRuleContext::acceptPrecede(std::vector<LNode> &v, int index) {

    auto stack = std::stack<int>();

    // check for the precede rule
    --index;

    if (!precede.empty()) {
        int pi = static_cast<int>(precede.size()) - 1;

        // while still LNodes to match
        while (pi >= 0) {

            // manage special chars
            while (index >= 0) {
                if (vectContains(ignore, v[index])) {   // skip ignored chars
                    --index;
                } else if (v[index].getId() == "]") {
                    stack.push(pi);       // store iterator
                    --index;
                } else if (v[index].getId() == "[") {
                    if (!stack.empty()) {
                        pi = stack.top();            // restore iterator from before the brackets
                        stack.pop();
                    }
                    --index;
                } else {
                    break;                          // stop skipping
                }
            }

            // try matching the char
            if (v[index].getId() != precede[pi].getId()) {   // no match
                if (!stack.empty()) {                   // if inside a bracket, skip bracket
                    index = skipToMatchingBracket(v, index, true);
                } else {                                // else return false
                    return false;
                }
            } else {                                // match
                --index;
                --pi;
            }
        }
    }
    return true;
}

bool LRuleContext::acceptFollow(std::vector<LNode> &v, int index) {

    auto stack = std::stack<int>();

    // check for the follow rule
    ++index;

    if (!follow.empty()) {
        auto pi = 0;

        // while still LNodes to match
        while (pi < follow.size()) {

            // manage special chars
            while (index < v.size()) {
                if (vectContains(ignore, v[index])) {   // skip ignored chars
                    ++index;
                } else if (v[index].getId() == "[") {
                    stack.push(std::move(pi));       // store iterator
                    ++index;
                } else if (v[index].getId() == "]") {
                    if (!stack.empty()) {
                        pi = stack.top();            // restore iterator from before the brackets
                        stack.pop();
                    }
                    ++index;
                } else {
                    break;                          // stop skipping
                }
            }

            // try matching the char
            if (v[index].getId() != follow[pi].getId()) {   // no match
                if (!stack.empty()) {                   // if inside a bracket, skip bracket
                    index = skipToMatchingBracket(v, index, false);
                } else {                                // else return false
                    return false;
                }
            } else {                                // match
                ++index;
                ++pi;
            }
        }
    }
    return true;
}
