//
// Created by revetoon on 3/4/19.
//

#include "LObject.hh"

#include <iostream>

LObject::LObject(std::vector<LNode> nodes) : nodes(std::move(nodes)){}

LObject::LObject(std::vector<LNode> nodes, const std::vector<LRule*> &rules) : nodes(std::move(nodes)) ,rules(rules) {}

LObject::LObject(std::vector<LNode> nodes, const std::vector<LRule *> &rules, Environment env)
    : nodes(std::move(nodes)),
      rules(rules),
      env(std::move(env))
{}

void LObject::iter() {
    auto newNodes = std::vector<LNode>();

    bool foundRule;

    int i = 0;
    while (i < nodes.size()) {
        foundRule = false;
        for (LRule *rule : rules) {
            int acceptSize = rule->accept(nodes, i, env);
            if (acceptSize > 0) {
                // RULE CAN BE APPLIED
                // use rule to add to new vector
                foundRule = true;

                i += acceptSize;

                for (const auto &n : rule->getResult()) {
                    newNodes.insert(newNodes.end(), std::move(n));
                }
                break;
            }
        }
        if (!foundRule) {
            // RULE CANNOT BE APPLIED
            // copy current node to new vector
            newNodes.insert(newNodes.end(), nodes[i]);
            ++i;
        }
    }
    nodes = newNodes;
}

void LObject::iterate(unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        iter();
        print();
    }
}

const std::vector<LRule*> &LObject::getRules() const {
    return rules;
}

const std::vector<LNode> &LObject::getNodes() const {
    return nodes;
}

void LObject::print() const {
    for (const auto& n : nodes) {
        std::cout << n.getId();
    }
    std::cout << std::endl;
}

