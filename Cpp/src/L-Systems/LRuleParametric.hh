//
// Created by revetoon on 3/14/19.
//

#ifndef OBJPARSER_LRULEPARAMETRIC_HH
#define OBJPARSER_LRULEPARAMETRIC_HH


#include <vector>
#include "Condition.hh"
#include "LRule.hh"

class LRuleParametric : public LRule {
public:
    bool accept(std::vector<LNode> &v, unsigned index, Environment &env) override;

    std::vector<LNode> getResult() override;

private:
    std::vector<LNode> fName;
    std::vector<LNode> finish;
    std::vector<Condition> cond;
    std::vector<LVar> params;


};


#endif //OBJPARSER_LRULEPARAMETRIC_HH
