//
// Created by revetoon on 3/6/19.
//

#ifndef OBJPARSER_LRULESTOCH_HH
#define OBJPARSER_LRULESTOCH_HH


#include <vector>
#include "LRule.hh"
#include "LNode.hh"

template <typename T>
class LRuleStoch : public LRule<T> {

public:
    LRuleStoch(const std::vector<LNode<T>> &start, const std::vector<std::vector<LNode<T>>> &finishes, const std::vector<double> &probabilities);
    LRuleStoch(const std::vector<LNode<T>> &start, const std::vector<std::vector<LNode<T>>> &finishes);

    std::vector<LNode<T>> getResult() override;

private:
    std::vector<double> probabilities;
    std::vector<std::vector<LNode<T>>> finishes;
};

#include "LRuleStoch.hxx"

#endif //OBJPARSER_LRULESTOCH_HH
