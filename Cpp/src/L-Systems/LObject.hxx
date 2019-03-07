//
// Created by revetoon on 3/4/19.
//

//#include "LObject.hh"

#include <iostream>

template <typename T>
LObject<T>::LObject(std::vector<LNode<T>> nodes) : nodes(std::move(nodes)){}

template <typename T>
LObject<T>::LObject(std::vector<LNode<T>> nodes, const std::vector<LRule<T>*> &rules) : nodes(std::move(nodes)) ,rules(rules) {}

template <typename T>
void LObject<T>::iter() {
    auto newNodes = std::vector<LNode<T>>();

    auto it = nodes.begin();
    bool foundRule = false;

    for (; it < nodes.end(); ++it) {
        foundRule = false;
        for (LRule<T> *rule : rules) {
            if (rule->accept(it)) {
                // RULE CAN BE APPLIED
                // use rule to add to new vector
                foundRule = true;

                for (const auto &n : rule->getResult()) {
                    newNodes.insert(newNodes.end(), std::move(n));
                }
                break;
            }
        }
        if (!foundRule) {
            // RULE CANNOT BE APPLIED
            // copy current node to new vector
            newNodes.insert(newNodes.end(), *it);
        }
    }
    nodes = newNodes;
}

template <typename T>
void LObject<T>::iterate(unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        iter();
    }
}

template<typename T>
const std::vector<LRule<T>*> &LObject<T>::getRules() const {
    return rules;
}

template<typename T>
const std::vector<LNode<T>> &LObject<T>::getNodes() const {
    return nodes;
}

