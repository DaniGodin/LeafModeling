//
// Created by revetoon on 3/6/19.
//

#ifndef OBJPARSER_LRULE_HH
#define OBJPARSER_LRULE_HH

#include <string>
#include <vector>
#include "LNode.hh"

class LRule {

public:
    virtual bool accept(std::vector<LNode>::iterator it) = 0;

    virtual std::vector<LNode> getResult() = 0;

    static std::vector<LNode> genRule(const std::string &rule);


protected:
    bool vectCmp(std::vector<LNode>::iterator lhs, std::vector<LNode>::iterator rhs, unsigned count);



protected:
};

#endif //OBJPARSER_LRULE_HH
