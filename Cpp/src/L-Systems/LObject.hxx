//
// Created by revetoon on 3/4/19.
//

//#include "LObject.hh"

template <typename T>
LObject<T>::LObject(std::vector<LNode<T>> nodes) : nodes(std::move(nodes)){}

template <typename T>
LObject<T>::LObject(std::vector<LNode<T>> nodes, const std::vector<LRule<T>> &rules) : nodes(std::move(nodes)) ,rules(rules) {}

template<typename T>
template<typename It1, typename It2>
bool LObject<T>::vectCmp(It1 lhs, It2 rhs, unsigned count) {
    for (unsigned i = 0; i < count; ++i) {
        if (*lhs != *rhs)
            return false;
        ++lhs;
        ++rhs;
    }
    return true;
}

template <typename T>
void LObject<T>::iter() {
    auto newNodes = std::vector<LNode<T>>();

    auto it = nodes.begin();
    bool foundRule = false;

    for (; it < nodes.end(); ++it) {
        foundRule = false;
        for (LRule<T> &rule : rules) {
            if (vectCmp(it, rule.getStart().begin(), rule.getStart().size())) {
                // RULE CAN BE APPLIED
                // use rule to add to new vector
                foundRule = true;
                for (const auto &n : rule.getFinish()) {
                    newNodes.insert(newNodes.end(), std::move(n));
                }
//                newNodes.insert(newNodes.end(), rule.getFinish().begin(), rule.getFinish().end());
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
const std::vector<LRule<T>> &LObject<T>::getRules() const {
    return rules;
}

template<typename T>
const std::vector<LNode<T>> &LObject<T>::getNodes() const {
    return nodes;
}

