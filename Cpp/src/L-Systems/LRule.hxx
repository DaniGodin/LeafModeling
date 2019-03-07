//
// Created by revetoon on 3/4/19.
//

#include <iostream>
#include "LRule.hh"

template<typename T>
LRule<T>::LRule(const std::vector<LNode<T>> &start):start(start) {}



template<typename T>
template<typename It1, typename It2>
bool LRule<T>::vectCmp(It1 lhs, It2 rhs, unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        if (*lhs != *rhs)
            return false;
        ++lhs;
        ++rhs;
    }
    return true;
}

template<typename T>
template<typename It1>
bool LRule<T>::accept(It1 it) {
    return vectCmp(it, start.begin(), start.size());
}

template<typename T>
std::vector<LNode<T>> LRule<T>::getResult() {
    std::cerr << "DO NOT USE" << std::endl;
    return std::vector<LNode<T>>();
}
