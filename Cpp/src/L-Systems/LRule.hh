//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LRULE_HH
#define OBJPARSER_LRULE_HH

#include <vector>
#include <string>
#include "LNode.hh"

template <typename T>
class LRule {
public:
    LRule(const std::vector<LNode<T>> &start, const std::vector<LNode<T>> &finish) : start(start), finish(finish) {}

    const std::vector<LNode<T>> &getStart() const {
        return start;
    }

    const std::vector<LNode<T>> &getFinish() const {
        return finish;
    }

    static std::vector<LNode<T>> genRule(const std::string &rule);

private:
    std::vector<LNode<T>>  start;
    std::vector<LNode<T>> finish;
};


#include "LRule.hxx"

#endif //OBJPARSER_LRULE_HH
