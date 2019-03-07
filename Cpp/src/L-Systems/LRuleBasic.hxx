//
// Created by revetoon on 3/4/19.
//

#include "LRuleBasic.hh"

template<typename T>
LRuleBasic<T>::LRuleBasic(const std::vector<LNode<T>> &start, const std::vector<LNode<T>> &finish)
        : LRule<T>(start), finish(finish) {}


template<typename T>
std::vector<LNode<T>> LRuleBasic<T>::getResult() {
    return finish;
}

