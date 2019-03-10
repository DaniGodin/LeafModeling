//
// Created by revetoon on 3/10/19.
//

#include "LRuleContext.hh"
#include <stack>

bool LRuleContext::accept(std::vector<LNode>::iterator it) {
    // check if "basic" rule apply
    if (!vectCmp(it, start.begin(), start.size()))
        return false;

    // check the precede
    if (!acceptPrecede(it))
        return false;

    // check the follow
    if (!acceptFollow(it))
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

void LRuleContext::skipToMatchingBracket(std::vector<LNode>::iterator &it, bool reverse) {
    int i = reverse ? -1 : 1;
    while (!(*it).getId().empty()) {
        if (reverse && (*it).getId() == "[")
            return;
        if (!reverse && (*it).getId() == "]")
            return;
        it += i;
    }
}

bool LRuleContext::acceptPrecede(const std::vector<LNode>::iterator &it) {

    auto stack = std::stack<std::vector<LNode>::iterator>();

    // check for the precede rule
    auto pit = std::move(it - 1);

    if (!precede.empty()) {
        auto p = precede.end() - 1;

        // while still LNodes to match
        while (!(*p).getId().empty()) {

            // manage special chars
            while (!(*pit).getId().empty()) {
                if (vectContains(ignore, *pit)) {   // skip ignored chars
                    --pit;
                } else if ((*pit).getId() == "]") {
                    stack.push(std::move(p));       // store iterator
                    --pit;
                } else if ((*pit).getId() == "[") {
                    if (!stack.empty()) {
                        p = stack.top();            // restore iterator from before the brackets
                        stack.pop();
                    }
                    --pit;
                } else {
                    break;                          // stop skipping
                }
            }

            // try matching the char
            if ((*pit).getId() != (*p).getId()) {   // no match
                if (!stack.empty()) {                   // if inside a bracket, skip bracket
                    skipToMatchingBracket(pit, true);
                } else {                                // else return false
                    return false;
                }
            } else {                                // match
                --pit;
                --p;
            }
        }
    }
    return true;
}

bool LRuleContext::acceptFollow(const std::vector<LNode>::iterator &it) {

    auto stack = std::stack<std::vector<LNode>::iterator>();

    // check for the precede rule
    auto fit = std::move(it + 1);

    if (!follow.empty()) {
        auto p = follow.begin();

        // while still LNodes to match
        while (!(*p).getId().empty()) {

            // manage special chars
            while (!(*fit).getId().empty()) {
                if (vectContains(ignore, *fit)) {   // skip ignored chars
                    ++fit;
                } else if ((*fit).getId() == "[") {
                    stack.push(std::move(p));       // store iterator
                    ++fit;
                } else if ((*fit).getId() == "]") {
                    if (!stack.empty()) {
                        p = stack.top();            // restore iterator from before the brackets
                        stack.pop();
                    }
                    ++fit;
                } else {
                    break;                          // stop skipping
                }
            }

            // try matching the char
            if ((*fit).getId() != (*p).getId()) {   // no match
                if (!stack.empty()) {                   // if inside a bracket, skip bracket
                    skipToMatchingBracket(fit, true);
                } else {                                // else return false
                    return false;
                }
            } else {                                // match
                ++fit;
                ++p;
            }
        }
    }
    return true;
}
