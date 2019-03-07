//
// Created by revetoon on 3/6/19.
//

#ifndef OBJPARSER_LRULE_HH
#define OBJPARSER_LRULE_HH

#include <string>
#include <vector>
#include "LNode.hh"

template <typename T>
class LRule {

protected:
    LRule(const std::vector<LNode<T>> &start);

public:
    template <typename It1>
    bool accept(It1 it);

    virtual std::vector<LNode<T>> getResult();

    template <typename It1, typename It2>
    bool vectCmp(It1 lhs, It2 rhs, unsigned count);

    static std::vector<LNode<T>> genRule(const std::string &rule);

    const std::vector<LNode<T>> &getStart() const {
        return start;
    }

protected:
    std::vector<LNode<T>> start;
};

#include "LRule.hxx"

#endif //OBJPARSER_LRULE_HH
