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
    LRuleParametric(const std::string &fName, const std::vector<LNode> &finish,
                    const std::vector<Condition> &cond, int paramCount);

    int accept(std::vector<LNode> &v, unsigned index, Environment &env) override;

    std::vector<LNode> getResult() override;

private:
    bool parseParams(const std::string &s);
    bool strCmp(const std::string &lhs, const std::string &rhs, int count);

private:
    std::string fName;
    std::vector<LNode> finish;
    std::vector<Condition> cond;
    int paramCount;
    std::vector<std::string> params;


};


#endif //OBJPARSER_LRULEPARAMETRIC_HH
