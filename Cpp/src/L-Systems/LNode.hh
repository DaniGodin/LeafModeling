//
// Created by revetoon on 3/4/19.
//

#ifndef OBJPARSER_LNODE_HH
#define OBJPARSER_LNODE_HH

template <typename T>
class LNode {

public:
    explicit LNode(T id);

    T getId() const;

    bool operator==(const LNode &rhs) const;

    bool operator!=(const LNode &rhs) const;

private:
    T id;
};

#include "LNode.hxx"

#endif //OBJPARSER_LNODE_HH
