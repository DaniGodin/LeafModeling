//
// Created by revetoon on 3/6/19.
//

#include <random>
#include <ctime>
#include "LRuleStoch.hh"


template<typename T>
LRuleStoch<T>::LRuleStoch(const std::vector<LNode<T>> &start, const std::vector<std::vector<LNode<T>>> &finishes,
                          const std::vector<double> &probabilities)
        : LRule(start), finishes(finishes), probabilities(probabilities)
{

}

template<typename T>
LRuleStoch<T>::LRuleStoch(const std::vector<LNode<T>> &start, const std::vector<std::vector<LNode<T>>> &finishes)
    : LRule(start), finishes(finishes) {

    double p = 1/finishes.size();
    probabilities = std::vector(finishes.size() - 1, p);
}


template<typename T>
std::vector<LNode<T>> LRuleStoch<T>::getResult() {
    std::srand(std::time(nullptr));
    float r = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);

    for (int i = 0; i < finishes.size() - 1; ++i) {
        try {
            if (r < probabilities[i]) {
                return finishes[i];
            }
            r -= probabilities[i];
        } catch (const std::exception &unused) {
            return finishes[i];
        }
    }

    // default
    return finishes[finishes.size() - 1];
}
