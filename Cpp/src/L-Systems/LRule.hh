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
    typedef std::vector<LNode>::iterator v_iter;
    typedef std::vector<LNode>::reverse_iterator v_riter;

public:
    virtual bool accept(std::vector<LNode> &v, unsigned index) = 0;

    virtual std::vector<LNode> getResult() = 0;

    static std::vector<LNode> genRule(const std::string &rule);


protected:
    bool vectCmp(v_iter lhs, v_iter rhs, unsigned count);



protected:
};

#endif //OBJPARSER_LRULE_HH
