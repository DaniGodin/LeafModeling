//
// Created by revetoon on 3/6/19.
//

#ifndef OBJPARSER_LRULE_HH
#define OBJPARSER_LRULE_HH

#include <string>
#include <vector>
#include "LNode.hh"

class LRule {

protected:
    LRule(const std::vector<LNode> &start);

public:
    virtual bool accept(std::vector<LNode>::iterator it);

    virtual std::vector<LNode> getResult();

    template <typename It1, typename It2>
    bool vectCmp(It1 lhs, It2 rhs, unsigned count);

    static std::vector<LNode> genRule(const std::string &rule);

    const std::vector<LNode> &getStart() const {
        return start;
    }

protected:
    std::vector<LNode> start;
};

#endif //OBJPARSER_LRULE_HH
