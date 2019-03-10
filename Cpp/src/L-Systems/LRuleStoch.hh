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

    const std::vector<std::vector<LNode>> &getFinish() const {
        return finishes;
    }

    const std::vector<LNode> &getStart() const {
        return start;
    }

    std::vector<LNode> getResult() override;

    bool accept(std::vector<LNode> &v, unsigned index) override;

private:
    std::vector<LNode> start;
    std::vector<double> probabilities;
    std::vector<std::vector<LNode>> finishes;
};


#endif //OBJPARSER_LRULESTOCH_HH
