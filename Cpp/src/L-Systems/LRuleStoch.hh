//
// Created by revetoon on 3/6/19.
//

#ifndef OBJPARSER_LRULESTOCH_HH
#define OBJPARSER_LRULESTOCH_HH


#include <vector>
#include "LRule.hh"
#include "LNode.hh"

class LRuleStoch : public LRule {

public:
    LRuleStoch(const std::vector<LNode> &start, const std::vector<std::vector<LNode>> &finishes, const std::vector<double> &probabilities);
    LRuleStoch(const std::vector<LNode> &start, const std::vector<std::vector<LNode>> &finishes);

    std::vector<LNode> getResult() override;

private:
    std::vector<double> probabilities;
    std::vector<std::vector<LNode>> finishes;
};


#endif //OBJPARSER_LRULESTOCH_HH
