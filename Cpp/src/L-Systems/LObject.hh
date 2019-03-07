//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LOBJECT_HH
#define OBJPARSER_LOBJECT_HH


#include <vector>
#include "LNode.hh"
#include "LRuleBasic.hh"

template <typename T>
class LObject {
public:
    explicit LObject(std::vector<LNode<T>> nodes);

    LObject(std::vector<LNode<T>> nodes, const std::vector<LRule<T>*> &rules);

    const std::vector<LRule<T>*> &getRules() const;

    const std::vector<LNode<T>> &getNodes() const;

    void iterate(unsigned count);

private:

    void iter();


private:
    std::vector<LRule<T>*> rules;
    std::vector<LNode<T>> nodes;

};

#include "LObject.hxx"

#endif //OBJPARSER_LOBJECT_HH
