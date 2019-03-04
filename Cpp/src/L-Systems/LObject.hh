//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LOBJECT_HH
#define OBJPARSER_LOBJECT_HH


#include <vector>
#include "LNode.hh"
#include "LRule.hh"

template <typename T>
class LObject {
public:
    explicit LObject(std::vector<LNode<T>> nodes);

    LObject(std::vector<LNode<T>> nodes, const std::vector<LRule<T>> &rules);

    const std::vector<LRule<T>> &getRules() const;

    const std::vector<LNode<T>> &getNodes() const;

    void iterate(unsigned count);

private:

    void iter();

    template <typename It1, typename It2>
    bool vectCmp(It1 lhs, It2 rhs, unsigned count);

private:
    std::vector<LRule<T>> rules;
    std::vector<LNode<T>> nodes;

};

#include "LObject.hxx"

#endif //OBJPARSER_LOBJECT_HH
