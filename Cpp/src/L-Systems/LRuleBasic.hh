//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LRULEBASIC_HH
#define OBJPARSER_LRULEBASIC_HH

#include <vector>
#include <string>
#include "LNode.hh"
#include "LRule.hh"

class LRuleBasic : public LRule {
public:
    LRuleBasic(const std::vector<LNode> &start, const std::vector<LNode> &finish);

    const std::vector<LNode> &getFinish() const {
        return finish;
    }

    std::vector<LNode> getResult() override;

private:
    std::vector<LNode> finish;
};



#endif //OBJPARSER_LRULEBASIC_HH
