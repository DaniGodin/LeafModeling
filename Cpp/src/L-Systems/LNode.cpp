//
// Created by revetoon on 3/4/19.
//

#include "LNode.hh"

std::string LNode::getId() const {
    return id;
}

LNode::LNode(const std::string &id) : id(id) {}

bool LNode::operator==(const LNode &rhs) const {
    return id == rhs.id;
}

bool LNode::operator!=(const LNode &rhs) const {
    return !(rhs == *this);
}
