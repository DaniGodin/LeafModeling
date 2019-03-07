//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LRULEBASIC_HH
#define OBJPARSER_LRULEBASIC_HH

#include <vector>
#include <string>
#include "LNode.hh"
#include "LRule.hh"

template <typename T>
class LRuleBasic : public LRule<T> {
public:
    LRuleBasic(const std::vector<LNode<T>> &start, const std::vector<LNode<T>> &finish);

    const std::vector<LNode<T>> &getFinish() const {
        return finish;
    }

    std::vector<LNode<T>> getResult() override;

private:
    std::vector<LNode<T>> finish;
};


#include "LRuleBasic.hxx"

#endif //OBJPARSER_LRULEBASIC_HH
